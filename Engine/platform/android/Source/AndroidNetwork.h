#ifndef _H_NETWORK_ANDROID
#define _H_NETWORK_ANDROID

#include "Common.h"

namespace AGK
{
	class cFile;

	class cLock 
	{
		protected:
			pthread_mutex_t mutex;
						
		public:
			cLock()
			{
				pthread_mutexattr_t attr;
				pthread_mutexattr_init( &attr );
				pthread_mutexattr_settype( &attr, PTHREAD_MUTEX_RECURSIVE );
				pthread_mutex_init( &mutex, &attr );
			}

			~cLock()
			{
				pthread_mutex_destroy( &mutex );
			}

			bool Acquire()
			{
				pthread_mutex_lock( &mutex );
				return true;
			}

			void Release()
			{
				pthread_mutex_unlock( &mutex );
			}
	};

#if __ARM_ARCH__ > 5
	// spin locks are faster, but not recursive and must not be used on single core devices
	class cSpinLock 
	{
		protected:
			volatile int iLock;
			
		public:
			cSpinLock() { iLock = 0; }

			~cSpinLock() { }

			bool Acquire()
			{
				asm volatile ( "mov r1, #0x1 \n\t"
					 "1: ldrex r0, [%0] \n\t"
						"cmp r0, #0 \n\t"
						"strexeq r0, r1, [%0] \n\t"
						"cmpeq r0, #0 \n\t"
						"bne 1b \n\t"
						"dmb \n\t"
						: 
						: "r"(&iLock)
						: "r0", "r1" );
						
				return true;
			}

			void Release()
			{
				asm volatile ( "dmb;" );
				iLock = 0;
			}
	};
#else
	class cSpinLock 
	{
		protected:
			pthread_mutex_t mutex;
			
		public:
			cSpinLock() 
			{ 
				pthread_mutexattr_t attr;
				pthread_mutexattr_init( &attr );
				pthread_mutex_init( &mutex, &attr );
			}

			~cSpinLock()
			{
				pthread_mutex_destroy( &mutex );
			}

			bool Acquire()
			{
				pthread_mutex_lock( &mutex );
				return true;
			}

			void Release()
			{
				pthread_mutex_unlock( &mutex );
			}
	};
#endif

	class cCondition 
	{
		protected:
			pthread_cond_t condition;
			pthread_mutex_t mutex;
			bool m_bLocked;
			
		public:
			cCondition()
			{
				pthread_cond_init( &condition, NULL );
				pthread_mutexattr_t attr;
				pthread_mutexattr_init( &attr );
				pthread_mutex_init( &mutex, &attr );
				m_bLocked = false;
			}

			~cCondition()
			{
				pthread_mutex_destroy( &mutex );
				pthread_cond_destroy( &condition );
			}

			void Lock()
			{
				pthread_mutex_lock( &mutex );
				m_bLocked = true;
			}

			void Unlock()
			{
				m_bLocked = false;
				pthread_mutex_unlock( &mutex );
			}

			void Wait()
			{
				pthread_cond_wait( &condition, &mutex );
				//pthread_cond_timeout_np( &condition, &mutex, 50 );
			}

			void Signal()
			{
				pthread_cond_signal( &condition );
			}

			void Broadcast()
			{
				pthread_cond_broadcast( &condition );
			}
	};
	
	class AGKPacket
	{
	protected:
		char m_Buffer[ AGK_NET_PACKET_SIZE ];
		UINT m_iPtr;
		
	public:
		
		AGKPacket();
		~AGKPacket(){};
		void Copy( const AGKPacket *fromPacket );
		
		void AddData( const char* s, UINT length );
		void AddString( const char *s );
		void AddChar( char c );
		void AddUInt( UINT u );
		void AddInt( int i );
		void AddFloat( float f );
		
		UINT GetPos() const;
		void SetPos( UINT pos );
		const char* GetBuffer() const { return m_Buffer; }
		char* GetRaw() { return m_Buffer; }
		
		UINT	GetData( char* data, UINT length );
		int		GetString( uString &s );		
		char	GetChar();						
		int		GetInt();						
		UINT	GetUInt();						
		float	GetFloat();					
	};

	class AGKSocket : public AGKThread
	{
	public:
		AGKSocket *m_pNext;
		
	protected:
		int m_client;
		char m_szIP[ 40 ];
		UINT m_port;
		volatile bool m_bConnected;
		volatile bool m_bConnecting;
		bool m_bDisconnected;
		UINT m_iTimeout;
		
		volatile float m_fProgress;
		volatile bool m_bResult;
		
		char m_sendBuffer[ 1400 ];
		UINT m_iSendWritePtr;
		
		UINT Run();
		
		void Reset();
		
	public:
		
		AGKSocket();
		AGKSocket( int s );
		~AGKSocket();

		const char *GetRemoteIP() { return m_szIP; }
		
		bool Flush();
		void Close( bool bGraceful=true );	
		void ForceClose();
		bool GetDisconnected() { return m_bDisconnected; }
		
		bool Connect( const char* IP, UINT port, UINT timeout=3000 );
		bool IsConnected() { return m_bConnected; }
		bool IsConnecting() { return m_bConnecting; }
		float GetProgress() { return m_fProgress; }
		
		bool SendFile( const char* szFilename );
		bool SendData( const char* s, int length );
		bool SendString( const char *s );
		bool SendChar( char c );
		bool SendUInt( UINT u );
		bool SendInt( int i );
		bool SendFloat( float f );
		
		// if this is zero the recv commands will block
		int GetBytes();
		
		int		RecvData( char* data, int length ); // blocks
		int		RecvString( uString &s );			// blocks
		char	RecvChar();							// blocks
		int		RecvInt();							// blocks
		UINT	RecvUInt();							// blocks
		float	RecvFloat();						// blocks			
	};
	
	class UDPManager
	{
	protected:
		int m_socket;
		UINT m_port;
		
	public:
		UDPManager( UINT port );
		~UDPManager();
		
		bool SendPacket( const char *IP, const AGKPacket *packet ); // does not block
		bool RecvPacket( char *fromIP, AGKPacket *packet );  // does not block
	};

	// wil listen for new connections until stopped
	class cNetworkListener : public AGKThread
	{
		protected:
			int m_socket;
			UINT m_port;
			cLock m_lock;

			AGKSocket* volatile m_pConnections;

			UINT Run();

		public:
			cNetworkListener();
			~cNetworkListener();

			AGKSocket* GetNewConnection();
			void AcceptConnections( UINT port );
			void Stop();
	};

	// will wait forever for broadcast packets until Stop() is called
	class BroadcastListener
	{
		protected:
			int m_socket;
			sockaddr_in addr;
			//char m_data[1500];
			//char m_from[45];
			//void (*callback)(int, const char*, const char*);

			//UINT Run();

		public:
			BroadcastListener();
			~BroadcastListener();
		
			void Close();

			bool SetListenPort( UINT port );
			bool ReceivedBroadcast();
			bool GetPacket( AGKPacket &packet, UINT &fromPort, char *fromIP );
	};

	// will broadcast a packet a regular intervals until stopped.
	class Broadcaster : public AGKThread
	{
		protected:
			AGKPacket m_packet;
			UINT m_interval;
			int m_max;
			UINT m_port;

			UINT Run();

		public:

			Broadcaster();
			~Broadcaster() {};

			// sets the data that will be broadcast every interval milliseconds for a maximum of max broadcasts (0=forever)
			// start with Start() and stop with Stop()
			void SetData( UINT port, const AGKPacket *packet, UINT interval, int max=0 );
	};
	
	class cHTTPConnection : public AGKThread
	{
		protected:
			void* request;
			uString m_sHost;
			int m_iSecure;
			
			bool volatile m_bConnected;
			float volatile m_fProgress;

			bool m_bSaveToFile;
			uString m_szServerFile;
			uString m_szLocalFile;
			uString m_szUploadFile;
			char m_szContentType[50];
			
			uString m_sResponse;
			cFile *m_pFile;
			uString m_sRndFilename;
			int m_iReceived;
			uString m_szPostData;
			int m_iSent;
			int m_iSendLength;
			cFile *m_pUploadFile;
			bool m_bFailed;
			
			void SendRequestInternal();
			void SendFileInternal();
			UINT Run();
			
		public:
			cHTTPConnection();
			~cHTTPConnection();
			
			int RecvData( void* buf, int size );
			int SendData( void* buf, int size );
						
			void Stop();
			
			bool SetHost( const char *szHost, int iSecure, const char *szUser=0, const char *szPass=0 );
			void Close();

			float GetProgress() { return m_fProgress; }
			
			// caller must delete returned pointer
			char* SendRequest( const char *szServerFile, const char *szPostData=0 ); //blocks
			bool SendRequestASync( const char *szServerFile, const char *szPostData=0 ); //does not block
			bool SendFile( const char *szServerFile, const char *szPostData, const char *szLocalFile ); //does not block

			int GetResponseReady();
			const char* GetResponse(); // caller must NOT delete returned pointer
			const char* GetContentType();

			bool DownloadFile( const char *szServerFile, const char *szLocalFile, const char *szPostData=0 ); //does not block
			bool DownloadComplete();
	};
}

#endif

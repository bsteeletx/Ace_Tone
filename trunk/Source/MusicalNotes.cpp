#include "MusicalNotes.h"
#include "AGKCore.h"

Notes::Notes()
: PhysicsS()
{
	_ThisNote = NOTEERROR;

	for (int i = 0; i < 4; i++)
	{
		_SplitNotes[i] = new PhysicsS();
		_SplitNotes[i]->SetOff();
		_SplitNotes[i]->SetVisible(false);
	}

	_exploded = false;
}

Notes::Notes(NoteValues NV, Sprite Clone)
: PhysicsS(Clone)
{
	_ThisNote = NV;
	_exploded = false;
}

Notes::Notes(unsigned int imageNumber, RFTPoint Begin, RFTPoint End)
: PhysicsS(imageNumber, Begin, End)
{
	_exploded = false;
}

Notes::~Notes()
{

}

Notes* Notes::CopySection(RFTPoint Begin, RFTPoint End)
{
	Notes *Copied = new Notes(GetImageID(), Begin, End);

	Copied->_ThisNote = NOTEERROR;
	Copied->SetOn();

	return Copied;
}

void Notes::Delete()
{
	for (int i = 0; i < 4; i++)
		_SplitNotes[i]->Delete();

	PhysicsS::Delete();
}

void Notes::Explode()
{
	float width = GetWidth();
	float height = GetHeight();

	//mark as visible and turn on physics
	for (int i = 0; i < 4; i++)
	{
		_SplitNotes[i]->SetOn();
		_SplitNotes[i]->SetVisible(true);
	}
	
	//Find coords of new Top Image
	RFTPoint TopLeft = GetPosition();

	//set up split sprites to replace original sprite
	_SplitNotes[0]->SetPosition(TopLeft);
	_SplitNotes[1]->SetPosition(TopLeft.GetX() + width*0.5f, TopLeft.GetY());
	_SplitNotes[2]->SetPosition(TopLeft.GetX(), TopLeft.GetY() + height*0.5f);
	_SplitNotes[3]->SetPosition(TopLeft.GetX() + width*0.5f, TopLeft.GetY() + height*0.5f);

	//hide and move original image (deletion happens later)
	SetVisible(false);
	SetPosition(RFTPoint(100.0f, 100.0f));

	//Set Offsets for both sprites to be in join position
	_SplitNotes[0]->SetOffset(RFTPoint(_SplitNotes[0]->GetWidth(), _SplitNotes[0]->GetHeight())); //bottom right
	_SplitNotes[1]->SetOffset(RFTPoint(0.0f, _SplitNotes[1]->GetHeight())); //bottom left
	_SplitNotes[2]->SetOffset(RFTPoint(_SplitNotes[2]->GetWidth(), 0.0f)); //top right
	_SplitNotes[3]->SetOffset(RFTPoint(0.0f, 0.0f)); //top left

	//Give an impulse to both sprites
	RFTPoint LeftPower = RFTPoint(-8.0f, 0.0f);
	RFTPoint UpPower = RFTPoint(0.0f, -8.0f);
	RFTPoint RightPower = RFTPoint(8.0f, 0.0f);
	RFTPoint DownPower = RFTPoint(0.0f, 8.0f);

	_SplitNotes[0]->SetImpulse(Vector(LeftPower, UpPower));
	_SplitNotes[1]->SetImpulse(Vector(RightPower, UpPower));
	_SplitNotes[2]->SetImpulse(Vector(LeftPower, DownPower));
	_SplitNotes[3]->SetImpulse(Vector(RightPower, DownPower)); 

	_exploded = true;
}

bool Notes::GetExploded()
{
	return _exploded;
}

NoteValues Notes::GetNoteValue()
{
	return _ThisNote;
}

void Notes::Init(unsigned int parentID)
{
	Text SplitBase[4] = { "Top_pick.png", "Right_pick.png", "Bottom_pick.png", "Left_pick.png" };
	Text Base = "";

	/*switch (_ThisNote)
	{
	case A:
		Base = "A";
		break;
	case B:
		Base = "B";
		break;
	default:
		Base = "C";
		break;
	} */

	/*for (int i = 0; i < 4; i++)
	{
		AGKCore Converter;
		SplitBase[i] = Base;
		//SplitBase[i] += Converter.Str(i);
		SplitBase[i] += ".png";
	} */

	for (int i = 0; i < 4; i++)
	{
		_SplitNotes[i] = new PhysicsS(parentID, SplitBase[i]);
		_SplitNotes[i]->SetOff();
		_SplitNotes[i]->SetVisible(false);
		_SplitNotes[i]->SetSize(5.0f);
	}
}

void Notes::Update()
{
	bool allGone = true;;
	//find out which ones are offscreen
	for (unsigned int i = 0; i < 4; i++)
	{
		if (!_SplitNotes[i]->GetExists())
			break;

		RFTPoint Position = _SplitNotes[i]->GetPosition();

		if (Position.GetX() > 100.0f || Position.GetX() < -50.0f)
		{
			_SplitNotes[i]->Delete();
			}
		else if (Position.GetY() > 150.0f)
		{
			_SplitNotes[i]->Delete();
		}

		allGone = false;
	}

	if (allGone)
		Delete();
}
package com.facebook;

import android.database.CursorIndexOutOfBoundsException;

import java.util.ArrayList;
import java.util.Collection;

class SimpleGraphObjectCursor<T extends GraphObject> implements GraphObjectCursor<T> {
    private int pos = -1;
    private boolean closed = false;
    private ArrayList<T> graphObjects = new ArrayList<T>();
    private boolean moreObjectsAvailable = false;
    private boolean fromCache = false;

    SimpleGraphObjectCursor() {
    }

    SimpleGraphObjectCursor(SimpleGraphObjectCursor<T> other) {
        pos = other.pos;
        closed = other.closed;
        graphObjects = new ArrayList<T>();
        graphObjects.addAll(other.graphObjects);
        fromCache = other.fromCache;

        // We do not copy observers.
    }

    public void addGraphObjects(Collection<T> graphObjects, boolean fromCache) {
        this.graphObjects.addAll(graphObjects);
        // We consider this cached if ANY results were from the cache.
        this.fromCache |= fromCache;
    }

    public boolean isFromCache() {
        return fromCache;
    }

    public void setFromCache(boolean fromCache) {
        this.fromCache = fromCache;
    }

    public boolean areMoreObjectsAvailable() {
        return moreObjectsAvailable;
    }

    public void setMoreObjectsAvailable(boolean moreObjectsAvailable) {
        this.moreObjectsAvailable = moreObjectsAvailable;
    }

    public int getCount() {
        return graphObjects.size();
    }

    public int getPosition() {
        return pos;
    }

    public boolean move(int offset) {
        return moveToPosition(pos + offset);
    }

    public boolean moveToPosition(int position) {
        final int count = getCount();
        if (position >= count) {
            pos = count;
            return false;
        }

        if (position < 0) {
            pos = -1;
            return false;
        }

        pos = position;
        return true;
    }

    public boolean moveToFirst() {
        return moveToPosition(0);
    }

    public boolean moveToLast() {
        return moveToPosition(getCount() - 1);
    }

    public boolean moveToNext() {
        return moveToPosition(pos + 1);
    }

    public boolean moveToPrevious() {
        return moveToPosition(pos - 1);
    }

    public boolean isFirst() {
        return (pos == 0) && (getCount() != 0);
    }

    public boolean isLast() {
        final int count = getCount();
        return (pos == (count - 1)) && (count != 0);
    }

    public boolean isBeforeFirst() {
        return (getCount() == 0) || (pos == -1);
    }

    public boolean isAfterLast() {
        final int count = getCount();
        return (count == 0) || (pos == count);
    }

    public T getGraphObject() {
        if (pos < 0) {
            throw new CursorIndexOutOfBoundsException("Before first object.");
        }
        if (pos >= graphObjects.size()) {
            throw new CursorIndexOutOfBoundsException("After last object.");
        }
        return graphObjects.get(pos);
    }

    public void close() {
        closed = true;
    }

    public boolean isClosed() {
        return closed;
    }

}

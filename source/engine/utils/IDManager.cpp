#include "IDManager.h"

IDManager::IDManager(int size):
    mUsed (size, false),
    mSize (size)
{
    for(int i=0; i<size; i++)
    {
        mIds.push(i);
    }
}

/* get next free id */
int IDManager::Next()
{
    if(!HasNext())
    {
        return -1;
    }

    int id = mIds.front();
    mIds.pop();
    mUsed[id] = true;

    return id;
}

/* return an unused id */
void IDManager::Refund(int id)
{
    if(id >= 0 && id < mSize && mUsed[id])
    {
        mIds.push(id);
        mUsed[id] = false;
    }
}

/* check if has any id available */
bool IDManager::HasNext() const
{
    return !mIds.empty();
}
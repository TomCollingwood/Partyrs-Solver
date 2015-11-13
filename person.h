#ifndef PERSON_H__
#define PERSON_H__

#define cols 4
#define rows 3

enum boolean{false, true};

typedef struct
{
  int ID;
  int wantsID;
  int wantsID2;
  int avoidID;
  enum boolean canmove;
	int holding;
}Person;

#endif

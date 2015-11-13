#include <stdio.h>
#include <stdlib.h>
#include "person.h"

Person addperson(int ID, int wantsID, int wantsID2, int avoidID, int holding);
enum boolean checkdup(int index, int list[]);
Person addobject(int ID);
enum boolean evaluatemap(int r, int c, Person map[][cols]);

/* Function maximum definition */
/* x, y and z are parameters */
int maximum(int x, int y, int z) {
  int max = x; /* assume x is the largest */

  if (y < max) { /* if y is larger than max, assign y to max */
    max = y;
  } /* end if */

  if (z < max) { /* if z is larger than max, assign z to max */
    max = z;
  } /* end if */

  return max; /* max is the largest value */
} /* end function maximum */


int main()
{
  setvbuf (stdout, NULL, _IONBF, 0);
  Person map[rows][cols]={
  {addobject(-3),addperson(1,-2,0,3,6),addperson(2,0,0,6,0),addobject(-4)},
  {addobject(-1),addperson(3,-4,0,0,0),addperson(4,5,0,0,0),addobject(-3)},
  {addobject(-2),addobject(-2),addperson(5,-3,0,0,0),addobject(-1)}
    };

  enum boolean solved = false;

  int numberofswaps = 7;
  int randomlistsize = numberofswaps*4;

  int randomlist[randomlistsize];
  int counter = 0;
  int counterlimit = 5;

  while(solved == false && counter < counterlimit){
    for(int i = 0; i<randomlistsize; i++){
      if (i % 2 == 0){
        randomlist[i] = rand() % rows;
      }
      else{
        randomlist[i] = rand() % cols;
        while(map[randomlist[i-1]][randomlist[i]].canmove == false){
          randomlist[i-1] = rand() % rows;
          randomlist[i] = rand() % cols;
        }
      }
    }
    for(int i =0; i<randomlistsize;i++){
      printf("%d",randomlist[i]);
    }
    // now random swapping
    for(int i = 0; i<randomlistsize; i+=4){
      Person temp	 = map[i][i+1];
      map[i][i+1] = map[i+2][i+3];
      map[i+2][i+3] = temp;
    }

    // evaluate

    Person map2[rows][cols]={
      {addobject(-3),addperson(2,0,0,6,0),addperson(3,-4,0,0,0),addobject(-4)},
      {addobject(-1),addperson(4,5,0,0,0),addperson(5,-3,0,0,0),addobject(-3)},
      {addobject(-2),addobject(-2),addperson(1,-2,0,3,6),addobject(-1)}
     };

    int evaluation = evaluatemap(rows, cols, map2);
    if(evaluation == true){
      printf("Done at %d iterations",counter);
    }
    solved = evaluation;
    if(counter == counterlimit -1){
      printf("Failed");
    }
    counter++;
  }
  return EXIT_SUCCESS;
}

Person addperson(int ID, int wantsID, int wantsID2, int avoidID, int holding){
  Person addee;
  addee.ID = ID;
  addee.wantsID = wantsID;
  addee.wantsID2 = wantsID2;
  addee.avoidID = avoidID;
  addee.canmove = true;
  addee.holding = holding;
  return addee;
}

enum boolean checkdup(int index, int list[]){
  enum boolean result = false;
  for(int i = 0; i < index-1; i+=2)
  {
    if(list[index-1]==list[i] && list[index]==list[i+1])
    {
      result = true;
    }
  }
  return result;
}

Person addobject(int ID)
{
  Person addee;
  addee.ID = ID;
  addee.wantsID = 0;
  addee.wantsID2 = 0;
  addee.avoidID = 0;
  addee.canmove = false;
  addee.holding = 0;
  return addee;
}

enum boolean evaluatemap(int r, int c, Person map[][cols]){
  enum boolean result = true;
  int counter1=0;
  int counter2=0;
  int counter3=0;
  for(int i=0; i<r; i++){
    for(int j=0; j<c; j++){
      if(map[i][j].canmove == true){
        int checklist[4][2]={
          {(i+1),j},
          {(i-1),j},
          {i,(j+1)},
          {i,(j-1)}
        };
        int avoidCheck = true;
        enum boolean IDcheck = false;
        enum boolean test1 = false;
        enum boolean test2 = false;
        for(int k=0; k<4; k++){
          int a = checklist[k][0];
          int b = checklist[k][1];
          enum boolean test3 = false;
          if(a>0 && b>0){
            // check wantsID to ID of nextto
            if(map[a][b].ID == map[i][j].wantsID){
              test1 = true;
            }
            if((map[i][j].wantsID2 == 0) || (map[a][b].ID == map[i][j].wantsID2)){
              test2 = true;
            }
            if((map[i][j].avoidID != map[a][b].ID) && (map[i][j].avoidID == 0 || map[i][j].avoidID != map[a][b].holding)){
              test3 = true;
            }
            // avoid check is definately right
            if(test3 == false){
              avoidCheck = false;
            }
          }
        }
        if(test1== true && test2 == true){
          IDcheck = true;
        }
        if(avoidCheck == true && IDcheck == true){
          result = true;
        }
      }
    }
  }
  return result;
}

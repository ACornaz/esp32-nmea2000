    /*
     * Circular Doubly Linked PageList for OBP60 Display
     */
#ifndef PAGE_H
#define PAGE_H
    
#include <Arduino.h>
#include "OBP60Data1.h"

extern struct pageNode *actualPage;
extern struct subPageNode *actualTile;
extern int numbOfPage;
extern String pageType[10];
extern String pageTile[10][4];


//  Page Node Declaration
struct subPageNode; 
class subPageList;

struct pageNode  // every pageNode has its own Node of subPage (=tiles)
{
        int numbTiles;
        bool first_view;
        struct pageNode *next;
        struct pageNode *prev;
        struct subPageNode *sub;
        subPageList *subList;  
};

class pageList
{
   public:
      int counter = 0;
      int light =0;  
      bool init=false;
      pageNode *start, *last;
      pageNode *createNode(int);
      void insertBegin(int);
      void insertLast(int);
      struct pageNode* insertAfterActualPos(int,struct pageNode*);
      struct pageNode* deleteActualPos(struct pageNode*);
      pageList()
      {
         counter = 0; 
         light=0;
         start = nullptr;
         last = nullptr;      
      }
};

struct subPageNode
{
   String title;
   String unit;
   float mean;  // dient nur zum debuggen: Mittelwert der Anzeige
   dataContainer * dContainer;  // actually used
   float * value;      // actually not used must be corrected
   char * charValue;   // actually not used must be corrected
   bool * valid;       // actually not used must be corrected
   struct subPageNode *next;
   struct subPageNode *prev;
   struct pageNode *superior;
};



class subPageList 
{
   public:
      int counter = 0; 
      subPageNode *start, *last; 
     // subPageNode *createSubNode(String title, String unit, float mean, float * val);
     // subPageNode *createSubNode(String title, String unit, float mean, char * val, bool * validPtr);
     // subPageNode *createSubNode(String title, String unit, dataContainer * containerPtr);
      subPageNode *createSubNode(String title, dataContainer * containerPtr);
     // subPageNode *insertBegin(String title, String unit, float mean, float * val);
     // subPageNode *insertLast(String title, String unit, float mean, float * val);
     // subPageNode *insertLast(String title, String unit, float mean, char * val, bool * validPtr);
     // subPageNode *insertLast(String title,  String unit, dataContainer * containerPtr);
      subPageNode *insertLast(String title, dataContainer * containerPtr);
     // void insertPos(String title, String unit, float mean, float * val);
      subPageList()
      {
         counter = 0; 
         start = nullptr;
         last = nullptr;
      }
};

String unit(String pageTile);
void makePageConsistent();

#endif

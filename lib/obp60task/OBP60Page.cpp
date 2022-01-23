//   Source Code for Page class
//   Open Boat Project
//   Multi Function Display OBP60

#include <Arduino.h>
#include "OBP60Page.h"

// DYNAMIC MEMORY ALLOCATION FOR PAGE NODE

pageNode* pageList::createNode(int numbofTiles)
{
   counter++;  
   struct pageNode *temp;
   temp = new(struct pageNode);
   temp->numbTiles = numbofTiles;
   temp->next = nullptr;
   temp->prev = nullptr;
   temp->subList  = new(subPageList);
   temp->keyAction="0";
   return temp;
}

// inserts pageNode at beginning
void pageList::insertBegin(int numbofTiles)
{
   struct pageNode *temp1;
   struct subPageNode *temp2;
   temp1 = createNode(numbofTiles);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp1;
      start->next = last->next = temp1;
      start->prev = last->prev = temp1;
      start->sub  = last->sub  = temp2;
   }
   else
   {
      // Element inserted in non empty list
      temp1->next = start;
      start->prev = temp1;
      start = temp1;
      start->prev = last;
      last->next = start;
      start->sub  = temp2;
   }
}
     
// inserts pageNode at last
void pageList::insertLast(int numbofTiles)
{
   struct pageNode *temp1;
   struct subPageNode *temp2;
   temp1 = createNode(numbofTiles);
   if (start == last && start == nullptr)
   {
      // Element inserted in empty list
      start = last = temp1;
      start->next = last->next = temp1;
      start->prev = last->prev = temp1;
      start->sub  = last->sub  = temp2;
   }
   else
   {
      // Element inserted in non empty list
      temp1->prev = last;
      last->next = temp1;
      last = temp1;
      last->next = start;
      start->prev = last;
      last->sub  = temp2;
   }
}

// inserts pageNode after actual position, not up to data 
struct pageNode* pageList::insertAfterActualPos(int numbofTiles, struct pageNode *actPage)
{                 
   struct pageNode *temp, *s, *ptr;
   temp = createNode(numbofTiles);
   if (start == last && start == nullptr)
   {  // empty Page List
      insertBegin(numbofTiles);   
   }
   else
   {
      s = actPage->next;
      actPage->next = temp;
      temp->prev = actPage;
      temp->next = s;
      s->prev=temp;
   }
   return(temp);
}

// Delete actual pageNode 
struct pageNode*  pageList::deleteActualPos(struct pageNode *actPage)   
{    
   pageNode *ptr;
   if (start == last && start == nullptr)
   {  // empty pageList
       return start;
   }
   actPage->prev->next = actPage->next;
   actPage->next->prev = actPage->prev;
   ptr=actPage->prev; 
   if(actPage == start) start = actPage->next;
   if(actPage == last) last = actPage->prev;
   free(actPage);
   counter--;
   return ptr;
}

/*
// dynamic memory allocation for subPageNode

subPageNode* subPageList::createSubNode(String title, String unit, float mean, float * val)
{
   counter++;  
   struct subPageNode *temp;
   temp = new(struct subPageNode);
  // temp->numberofSubPage = numb;
   temp->title= title;
   temp->unit = unit;
   temp->mean = mean;
   temp->value = val;
   temp->next = nullptr;
   temp->prev = nullptr;
   temp->superior  = nullptr;
   return temp;
}

subPageNode* subPageList::createSubNode(String title, String unit, float mean, char * val, bool * validPtr)
{
   counter++;  
   struct subPageNode *temp;
   temp = new(struct subPageNode);
  // temp->numberofSubPage = numb;
   temp->title= title;
   temp->unit = unit;
   temp->mean = mean;
   temp->charValue = val;
   temp->valid = validPtr;
   temp->next = nullptr;
   temp->prev = nullptr;
   temp->superior  = nullptr;
   return temp;
}


subPageNode* subPageList::createSubNode(String title, String unit, dataContainer * containerPtr)
{   
   counter++;  
   struct subPageNode *temp;
   temp = new(struct subPageNode);
  // temp->numberofSubPage = numb;
   temp->title= title;
   temp->unit = unit;
   temp->dContainer = containerPtr;
   temp->charValue = containerPtr->svalue;
   temp->valid = &containerPtr->valid;
   temp->next = nullptr;
   temp->prev = nullptr;
   temp->superior  = nullptr;
   return temp;

}

*/

// dynamic memory allocation for subPageNode
subPageNode* subPageList::createSubNode(String title, dataContainer * containerPtr)
{   
   counter++;  
   struct subPageNode *temp;
   temp = new(struct subPageNode);
  // temp->numberofSubPage = numb;
   //temp->title= title;
   temp->title= containerPtr->title;
   temp->unit = containerPtr->unit;
   temp->dContainer = containerPtr;
   temp->charValue = containerPtr->svalue;
   temp->valid = &containerPtr->valid;
   temp->next = nullptr;
   temp->prev = nullptr;
   temp->superior  = nullptr;
   return temp;

}

/*
// inserts element at beginning 
subPageNode* subPageList::insertBegin(String title, String unit, float mean, float * val)
{
   //dataContainer c;  // only for test : nonsense 
   struct subPageNode *temp;
   temp = createSubNode(title, unit, mean, val);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp;
      start->next = last->next = temp;
      start->prev = last->prev = temp;
   }
   else
   {
      temp->next = start;
      start->prev = temp;
      start = temp;
      start->prev = last;
      last->next = start;
   }
   return temp;
}
     
// inserts element at last 
subPageNode*  subPageList::insertLast(String title, String unit, float mean, float * val)
{
   struct subPageNode *temp;
   temp = createSubNode(title, unit, mean, val);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp;
      start->next = last->next = temp;
      start->prev = last->prev = temp;
   }
   else
   {
      last->next = temp;
      temp->prev = last;
      last = temp;
      start->prev = last;
      last->next = start;
   }
   return temp;
}

subPageNode*  subPageList::insertLast(String title, String unit, float mean, char * val, bool * validPtr)
{
   struct subPageNode *temp;
   //float mean=1.2;
   temp = createSubNode(title, unit, mean, val, validPtr);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp;
      start->next = last->next = temp;
      start->prev = last->prev = temp;
   }
   else
   {
      last->next = temp;
      temp->prev = last;
      last = temp;
      start->prev = last;
      last->next = start;
   }
   return temp;
}


subPageNode*  subPageList::insertLast(String title, String unit, dataContainer * containerPtr)
{
   
   struct subPageNode *temp;
   temp = createSubNode(title, unit, containerPtr);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp;
      start->next = last->next = temp;
      start->prev = last->prev = temp;
   }
   else
   {
      last->next = temp;
      temp->prev = last;
      last = temp;
      start->prev = last;
      last->next = start;
   }
   return temp;
}
*/

// inserts element at last 
subPageNode*  subPageList::insertLast(String title, dataContainer * containerPtr)
{
   
   struct subPageNode *temp;
   temp = createSubNode(title, containerPtr);
   if (start == last && start == nullptr)
   {    
     // Element inserted in empty list
      start = last = temp;
      start->next = last->next = temp;
      start->prev = last->prev = temp;
   }
   else
   {
      last->next = temp;
      temp->prev = last;
      last = temp;
      start->prev = last;
      last->next = start;
   }
   return temp;
}

/*
// inserts element at position, not up to date
void subPageList::insertPos(String title, String unit, float mean, float * val)
{    
   int value, pos, i;         
   struct subPageNode *temp, *s, *ptr;
   temp = createSubNode(title, unit, mean, val);
   if (start == last && start == nullptr)
   {
      if (pos == 1)
      {
         start = last = temp;
         start->next = last->next = nullptr;    
         start->prev = last->prev = nullptr;
      }
      else
      {
         counter--;
         return;
      }
   }  
   else
   {
      if (counter < pos)
      {
          counter--;
          return;      
      }
      s = start;    
      for (i = 1;i <= counter;i++)
      {
          ptr = s;
          s = s->next;
          if (i == pos - 1)
          {
              ptr->next = temp;
              temp->prev = ptr;
              temp->next = s;
              s->prev = temp;
              break;
          }
      }
   }
}
*/

String unit(String pageTile)  // unit doppelt definiert auch in Data !!!!!!!
{
   if((pageTile == "Off")||
      (pageTile == "GPSDate")||
      (pageTile == "GPSTime")||
      (pageTile == "HDOP")||
      (pageTile == "Latitude")||
      (pageTile == "Longitude")||
      (pageTile == "PDOP")|| 
      (pageTile == "SatInfo")||
      (pageTile == "VPOD")||
      (pageTile == "WPLatitude")||
      (pageTile == "WPLongitude"))  return("");
   if((pageTile == "AWA")||
      (pageTile == "COG")|| 
      (pageTile == "AWD")||
      (pageTile == "BTW")||
      (pageTile == "Deviation")||
      (pageTile == "Haeding")||
      (pageTile == "RudderAngleIndicator")||
      (pageTile == "TWA")||
      (pageTile == "TWD")||
      (pageTile == "Variation"))  return("deg");
   if((pageTile == "AWS")|| 
      (pageTile == "Max")||
      (pageTile == "AWS")||
      (pageTile == "Max")||
      (pageTile == "TWS")||
      (pageTile == "Max")||
      (pageTile == "STW")||
      (pageTile == "SOG")||
      (pageTile == "STW")||
      (pageTile == "TWS"))  return("kn");       
   if((pageTile == "Depth")||    
      (pageTile == "WaterDepth")) return("m");         
   if((pageTile == "DTW")||
      (pageTile == "Log")||
      (pageTile == "TripLog")|| 
      (pageTile == "XTE")) return("NM");                       
   if((pageTile == "ROT"))  return("deg/min");
   if((pageTile == "Timezone"))  return("h");
   if((pageTile == "WaterTemp")) return("C");
}

// corrects the manual inputs from webside and makes it consistent
void makePageConsistent()
{
   int np=0;  // number of Page
   int tile=0; // number of active tiles of page i
   int i=1;  
   for(int p=1; p<=6; p++)
   {  
      bool pageEmpty = true;
      for(int j=1;j<=4;j++)
      {
         if(pageTile[i][j]=="Off") 
            pageEmpty= pageEmpty && true;
         else
            pageEmpty= pageEmpty && false;
      }
      if(pageEmpty == true)
      { 
         if( pageType[i] == "1"  ||
             pageType[i] == "2"  ||
             pageType[i] == "3"  ||
             pageType[i] == "4"  ) pageType[i] = "Off";
      }
      if(pageType[i] == "Off")
      {
         for(int j=i;j<6;j++)
         {
            pageType[j]=pageType[j+1];
            for(int k=1;k<=4;k++)
            {
               pageTile[j][k]=pageTile[j+1][k];
            }
         }
         pageType[6]="Off";
         pageTile[6][1]="Off";
         pageTile[6][2]="Off";
         pageTile[6][3]="Off";
         pageTile[6][4]="Off";
      }
      else
      {
         np++;
         i++;
      }
   }
   for(int i=1;i<=np;i++)
   {  
      if(pageType[i]=="1" ||
         pageType[i]=="2" ||
         pageType[i]=="3" ||
         pageType[i]=="4" )
      {
         tile=0;     
         int k=1;
         for(int j=1;j<=4;j++)
         {
            if(pageTile[i][k] == "Off") 
            {   
               for(int m=k;m<4;m++)
               {
                  pageTile[i][m] = pageTile[i][m+1];
               }
               pageTile[i][4]="Off";
            }
            else{
               tile++;
               k++;
            }
         }

         if(pageType[i]=="Off") tile=0;
        
         switch (tile)
         {
            case 0:
               pageType[i] = "Off";
               break;
            case 1:
               pageType[i] = "1";
               break;
            case 2:
               pageType[i] = "2";
               break;
            case 3:
               pageType[i] = "3";
               break;
            case 4:
               pageType[i] = "4";
               break;
         }
      }
   }

   if(np==0) // no activated pages in wifi, config.json 
   {
      np=1;
      pageType[1] = "dummy";
   }
   numbOfPage=np; 
}
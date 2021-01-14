#ifndef _STORY_H__
#define _STORY_H__
#include <set>
#include <stack>
#include <string>

#include "exception.h"
#include "function.h"
#include "page.h"

//this function read the whole story under a given directory
//store the pages into a vector
std::vector<Page> readStory(const char * directory) {
  int pageNum = 1;
  std::vector<Page> pages;
  //initialize a vector and start with page number 1
  while (true) {
    std::string nameStr = fileName(directory, pageNum);
    //generate the file path
    const char * name = nameStr.c_str();
    if (!checkFile(name, pageNum)) {
      //check if the file exists
      //if page1.txt not exist, it throw expt and catch it inside
      //if it's not page1 and it does not exist
      //we are finished processing all consecutive pages and break
      break;
    }
    std::ifstream file(name);
    Page page(file, pageNum);
    pages.push_back(page);
    pageNum += 1;
  }
  //return the vectore that contains all pages
  return pages;
}
//only verify if a page has been referenced, cannot verify if it can be reached starting from page1
//aka some chain/circle of pages exists
//and pages reference each other excluding page1 in the chain/loop
bool validStory(std::vector<Page> & pages) {
  size_t range = pages.size();
  //use a vector of ints to show if a page has been referenced
  //int at index i denotes if page i+1 has been referenced
  //also use two ints to represent win and lose pages' existence
  //0 represents no, 1 represents yes
  int win = 0;
  int lose = 0;
  std::vector<int> pageValidation;
  for (size_t i = 0; i < range; i++) {
    pageValidation.push_back(0);
  }
  //initialize the pageValidation vector with all 0s
  //denoting that every page has not been referenced
  for (size_t i = 0; i < range; i++) {
    int type = pages[i].pageT();
    //for each page, check its type and set win or lose to 1 as needed
    if (type == 0) {
      win = 1;
    }
    else if (type == 1) {
      lose = 1;
    }
    else {
      //if it is a page with choices,
      //see its destination pages
      std::vector<int> destPages = pages[i].destPageNums();
      for (size_t j = 0; j < destPages.size(); j++) {
        //for each destination page number
        //see if it is in the range
        //e.g a story consists of 5 pages should not have any destination page number = 6
        size_t destP = destPages[j];
        if (destP <= 0 || destP > range) {
          std::cerr << "page " << i + 1 << std::endl;
          throw goNoWhere();
        }
        pageValidation[destP - 1] = 1;
        //also, for each valid destination page number
        //mark that corresponding page as referenced
      }
    }
  }
  for (size_t i = 0; i < range; i++) {
    if (pageValidation[i] != 1 && i != 0) {
      std::cerr << "page " << i + 1 << std::endl;
      throw notReferenced();
      //for any page never referenced
      //throw an expt
    }
  }
  if (win != 1 || lose != 1) {
    throw noResults();
    //if there is no win page or lose page
    //throw a corresponding expt
  }
  return true;
  //if all check passed
  //this is a valid story and we can return true
}

//this function is used to go through the story
//alowing the user to input numbers to choose their way of adventure
void startStory(std::vector<Page> & pages) {
  bool finished = false;
  size_t currPageN = 0;  //currPageN is the actual page num -1
  while (!finished) {
    Page currPage = pages[currPageN];
    std::vector<int> destPageNs = currPage.destPageNums();
    size_t choiceRange = destPageNs.size();
    int currPageT = currPage.pageT();
    currPage.printPage();
    //as long as the sory is not over,
    //print the current page
    if (currPageT == 0 || currPageT == 1) {
      finished = true;
      break;
      //if the current page is a win or lose page
      //story ends and jump out of the loop
    }
    bool validInput = false;
    //use a loop to get a valid number of choice input
    while (!validInput) {
      size_t holder;
      int num = getInputNum();
      //all invalid input that cannot be converted into a number will be assigned with -1
      if (num <= -1) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
        continue;
      }
      holder = num;
      if (holder == 0 || holder > choiceRange) {
        std::cout << "That is not a valid choice, please try again" << std::endl;
      }
      else {
        currPageN = destPageNs[holder - 1] - 1;
        validInput = true;
        //jump out of the input loop
        //continue the print loop with the next page prepared
      }
    }
  }
}

//check if pages in a story can be reached by starting at page 1
std::set<int> checkReachability(std::vector<Page> & pages) {
  std::set<int> reachable;
  reachable.insert(1);
  //page 1 is reachable
  bool change = true;
  size_t setSize = reachable.size();
  while (change) {
    //put the destination pages of all pages in reachable
    //and if the reachable set increases, do this again
    //until all reachable page numbers are in it and it remains same after one round of insertion
    std::set<int> temp;
    for (std::set<int>::iterator itS = reachable.begin(); itS != reachable.end(); ++itS) {
      Page curr = pages[*itS - 1];
      if (curr.pageT() == 2) {
        std::vector<int> destpages = curr.destPageNums();
        //the index of vector pages is 1 less than the actual page number
        std::vector<int>::iterator itV;
        for (itV = destpages.begin(); itV != destpages.end(); ++itV) {
          reachable.insert(*itV);
        }
      }
    }
    for (std::set<int>::iterator itS = temp.begin(); itS != temp.end(); itS++) {
      reachable.insert(*itS);
    }
    size_t sizeNow = reachable.size();
    if (setSize == sizeNow) {
      change = false;
    }
    else {
      setSize = sizeNow;
    }
  }
  //once we get all reachable page numbers, return it
  return reachable;
}

//print not reachable pages
void printNotReachable(std::set<int> & reachable, std::vector<Page> & pages) {
  int pagesSize = 0;
  for (std::vector<Page>::iterator itP = pages.begin(); itP != pages.end(); ++itP) {
    pagesSize++;
  }
  //for pages in the story, aka all pages in vector "pages"
  //if a page does not have its number in reachable set, print it with the given format
  for (int i = 0; i < pagesSize; i++) {
    std::set<int>::iterator itS;
    itS = reachable.find(i + 1);
    if (itS == reachable.end()) {
      std::cout << "Page " << i + 1 << " is not reachable" << std::endl;
    }
  }
}

//given a win page number
//use a stack to implement DFS
//find a path starting with page 1 and ending with page winPageN
void trackPath(std::vector<Page> & pages, int & winPageN) {
  std::stack<Page> pageStack;
  pageStack.push(pages[0]);
  //push page 1 into the stack
  Page * win = NULL;
  while (!pageStack.empty()) {
    //while the stack is not empty
    //pop the page on the top
    int currN = pageStack.top().getPageN();
    pageStack.pop();
    Page * curr = &(pages[currN - 1]);
    //if this page is the sin page we are looking for
    //use win to point to it and break
    if (currN == winPageN) {
      win = curr;
      break;
    }
    else {
      //if not, for each of its unvisited destination pages
      //set them as visited and set their previous page as the current page
      //then push them into the stack
      std::vector<int> pageNums = curr->destPageNums();
      for (std::vector<int>::iterator itV = pageNums.begin(); itV != pageNums.end();
           itV++) {
        int index = (*itV) - 1;
        if (!pages[index].getVisited()) {
          pages[index].setVisited();
          pages[index].setPrev(curr);
          pageStack.push(pages[index]);
        }
      }
    }
  }
  //now we have a pointer "win" pointing at our desired win page
  //and we can use the prev pointer repeatedly to generate the path
  //since we are tracking the path reversely and the requirement nedds it to be printed normally
  //a string stack is used to temporily store the output and we'll output them later
  std::stack<std::string> outputStack;
  int currN = win->getPageN();
  std::string format("Page ");
  std::string num = toString(currN);
  std::string output;
  output = format + num + " WIN";
  //format the output string
  outputStack.push(output);
  //this is a key point, how can we access the curr page
  //and know what choice its prev makes at the same time
  //to generate the output
  //getPrevChoice is defined in function.h and you may refer to that
  int prevChoice = getPrevChoice(win);
  std::string pChoiceNum = toString(prevChoice);
  Page * track = win->getPrev();
  while (track != NULL) {
    currN = track->getPageN();
    num = toString(currN);
    output = format + num + " Choice " + pChoiceNum;
    outputStack.push(output);
    if (track->getPrev() != NULL) {
      prevChoice = getPrevChoice(track);
      pChoiceNum = toString(prevChoice);
    }
    track = track->getPrev();
  }
  //output the path
  while (!outputStack.empty()) {
    std::string line = outputStack.top();
    std::cout << line << std::endl;
    outputStack.pop();
  }
}

//search for a win page in all pages reachable and track the path from page 1 to that win page
void findPath(std::set<int> & reachable, std::vector<Page> & pages) {
  int pagesSize = 0;
  for (std::vector<Page>::iterator itP = pages.begin(); itP != pages.end(); ++itP) {
    pagesSize++;
  }
  bool winable = false;
  int winPageN = 0;
  //search for a win page in the reachable set
  for (std::set<int>::iterator itS = reachable.begin(); itS != reachable.end(); itS++) {
    Page * curr = &pages[*itS - 1];
    if (curr->pageT() == 0) {
      winable = true;
      winPageN = *itS;
      //if found, record the winpage number and break
      break;
    }
  }
  if (!winable) {
    throw notWinable();
  }
  else {
    trackPath(pages, winPageN);
  }
}

#endif

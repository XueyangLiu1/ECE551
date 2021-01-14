#ifndef _PAGE_H__
#define _PAGE_H__
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "exception.h"
#include "function.h"
//class Page contains all info from a single page
class Page {
 private:
  //class Choices contains the text of choices and the destination page numbers
  //also if the page is a win page, lose page or regular page
  class Choices {
   public:
    std::vector<std::string> choices;
    std::vector<int> destPages;
    int type;
    // WIN = 0, LOSE = 1, CHOICES = 2
    Choices(std::vector<std::string> & choices,
            std::vector<int> & destPages,
            int & type) :
        choices(choices),
        destPages(destPages),
        type(type) {}
  };
  Choices * choices;
  Page * prev;
  std::vector<std::string> contents;
  int pageNum;
  bool visited;
  //pointer prev is used in step4 for tracking
  //contents is a vector which stores lines of story in the page
  //pageNum is the page's page number
  //visited is used in step4 as a mark for if the page is already visite

 public:
  Page() : choices(NULL), prev(NULL), pageNum(0), visited(false) {}
  //initialize the page object with a page file stream and its page number
  Page(std::ifstream & file, int & pageNum) :
      prev(NULL),
      pageNum(pageNum),
      visited(false) {
    //initialize two vectors to store the destination page numbers and choice texts
    std::vector<std::string> choices;
    std::vector<int> pageNums;
    //initialize a line to get the file's content
    std::string line;
    //this bool is to detect if there exist a line start with # in the file
    //to detect invalid file
    bool poundFlag = false;
    //default set the page's type as -1 before we know what it is
    int type = -1;
    while (!file.eof()) {
      std::getline(file, line);
      //while not reaching the end of the file, get the line
      if (!poundFlag) {
        //if we haven't seen the #
        //we are processing a choice line ro we just get the # line
        if (line[0] == '#') {
          poundFlag = true;
          continue;
          //if it is the pound line, weignore its content and process next line
        }
        //else, we are processing a choice line
        if (type == -1) {
          //if we haven't decide the page's type
          //we are processing the first line
          //set the page type according to the first line
          if (line.compare("WIN") == 0) {
            type = 0;
            continue;
          }
          else if (line.compare("LOSE") == 0) {
            type = 1;
            continue;
          }
          //for win page or lose page, the content of the first line is useless
          //so we continue and process the next
          else {
            //if the first line is not win nor lose
            //we are getting a choice line or an invalid line with arbitrary content
            //we detect that in storeC
            type = 2;
          }
        }
        //for any line before the # line, except for some situations above where we "continue"
        //others all require the line to be stored, as two parts:
        // the destnation page number and the text
        //this is done by a function defined in function.h
        storeC(choices, pageNums, line);
      }
      else {
        //if we have seen the # line
        //we are processing the story text on this page
        //just store them in vector contents
        contents.push_back(line);
      }
    }
    try {
      if (poundFlag == false) {
        //if there is no # line in the file, it is an eror
        throw noPound();
      }
      if (type == -1) {
        //if there is no win or lose or choices in the file, it is an error
        throw noChoices();
      }
    }
    catch (std::exception & e) {
      errmsg(e.what());
    }
    file.close();
    //create a Choices object with the vectors and the type
    //make the pointer choices point to it
    this->choices = new Choices(choices, pageNums, type);
  }
  Page(const Page & rhs) {
    this->choices =
        new Choices(rhs.choices->choices, rhs.choices->destPages, rhs.choices->type);
    this->contents.clear();
    for (size_t i = 0; i < rhs.contents.size(); i++) {
      this->contents.push_back(rhs.contents[i]);
    }
    this->prev = rhs.prev;
    this->visited = rhs.visited;
    this->pageNum = rhs.pageNum;
  }
  Page & operator=(const Page & rhs) {
    if (this != &rhs) {
      this->choices =
          new Choices(rhs.choices->choices, rhs.choices->destPages, rhs.choices->type);
      this->contents.clear();
      for (size_t i = 0; i < rhs.contents.size(); i++) {
        this->contents.push_back(rhs.contents[i]);
      }
      this->prev = rhs.prev;
      this->visited = rhs.visited;
      this->pageNum = rhs.pageNum;
    }
    return *this;
  }
  ~Page() { delete this->choices; }

  //print a single page out witht the required format
  void printPage() {
    //print the text first
    for (size_t i = 0; i < contents.size(); i++) {
      std::cout << contents[i] << std::endl;
    }
    //then print contents based on the page type
    int type = choices->type;
    if (type == 0) {
      std::cout << "Congratulations! You have won. Hooray!" << std::endl;
    }
    else if (type == 1) {
      std::cout << "Sorry, you have lost. Better luck next time!" << std::endl;
    }
    else {
      //if there are choices, print choices
      std::cout << "What would you like to do?" << std::endl << std::endl;
      for (size_t i = 0; i < choices->choices.size(); i++) {
        std::cout << i + 1 << ". " << choices->choices[i] << std::endl;
      }
    }
  }

  //provide the value of some private variables
  int pageT() const { return choices->type; }
  const std::vector<int> & destPageNums() const { return choices->destPages; }
  bool getVisited() const { return visited; }
  void setVisited() { this->visited = true; }
  int getPageN() const { return pageNum; }
  void setPrev(Page * prev) { this->prev = prev; }
  Page * getPrev() const { return prev; }
};

//For step4, we need to know what the choice number
//the prev page gets for curr page
int getPrevChoice(Page * curr) {
  //get a pointer point to the prev page
  if (curr->getPrev() == NULL) {
    return -1;
  }
  Page * prev = curr->getPrev();
  std::vector<int> preVDests = prev->destPageNums();
  int choiceNum = 1;
  int currNum = curr->getPageN();
  //iterate through the prev page's possible destination pages
  //find the curr's page number and record the choice number
  for (std::vector<int>::iterator itV = preVDests.begin(); itV != preVDests.end();
       itV++) {
    if (*itV == currNum) {
      break;
    }
    else {
      choiceNum += 1;
    }
  }
  return choiceNum;
}

#endif

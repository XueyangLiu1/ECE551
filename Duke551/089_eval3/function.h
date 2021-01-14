//this file contains some functions that are reusable
#ifndef _FUNCTION_H__
#define _FUNCTION_H__

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "exception.h"

//this function is used to convert string page numver to int
//any failure in conversion will be handled inside this function
int getPageNum(std::string & numStr) {
  //initialize pageNum as -1
  int pageNum = -1;
  //use string stream to convert
  std::istringstream conversion(numStr);
  if (!(conversion >> pageNum)) {
    pageNum = -1;
  }
  try {
    //if the string cannot be converted into int
    //throw the exception
    if (pageNum == -1) {
      throw strToNum();
    }
  }
  catch (std::exception & e) {
    errmsg(e.what());
  }
  //if no exception thrown
  //return the result
  return pageNum;
}

//this function is used to get a number input from cin
//and convert it to int type
//if the input cannot be converted, return -1
//and the code using this function will deal with it
//by letting the user keep inputting until we get a valid int
int getInputNum() {
  std::string input;
  getline(std::cin, input);
  int pageNum = -1;
  std::istringstream conversion(input);
  if (!(conversion >> pageNum)) {
    pageNum = -1;
  }
  return pageNum;
}
//convert a valid int to string
std::string toString(int & num) {
  std::string ans;
  std::ostringstream conversion;
  conversion << num;
  ans = conversion.str();
  return ans;
}
//given the directory name and the page number,
//return a file name string
//e.g. given ("story", 3), return "story/page3.txt"
std::string fileName(const char * directory, int & pageNum) {
  std::string fileName;
  std::ostringstream conversion;
  conversion << directory << "/page" << pageNum << ".txt";
  fileName = conversion.str();
  return fileName;
}

//check if a file exists
//num represents page number
bool checkFile(const char * name, int & num) {
  try {
    std::ifstream file(name);
    if (!file && num == 1) {
      //if num == 1, it means page1.txt not exist
      //this is an error
      throw noFile();
    }
    else if (!file) {
      //if num!=1 and the file does not exist
      // it means we have processed all pages
      //this is not an error, so simply return false
      return false;
    }
    file.close();
  }
  catch (std::exception & e) {
    std::cerr << name << std::endl;
    errmsg(e.what());
  }
  return true;
}

//storeC is used to process a single line of choice
//split the line to get destination page number and the text
//store them into different vectors with the right type
//this function is used when initializing a page object
void storeC(std::vector<std::string> & choices,
            std::vector<int> & pageNums,
            std::string & line) {
  std::size_t err = -1;
  std::size_t pos = line.find(":");
  if (pos == err) {
    errmsg("No : was found in the line.");
  }
  std::size_t numLen = pos;
  std::string numStr = line.substr(0, numLen);
  //getPageNum is defined earlier in function.h
  int pageNum = getPageNum(numStr);
  std::string text = line.substr(pos + 1);
  pageNums.push_back(pageNum);
  choices.push_back(text);
}

#endif

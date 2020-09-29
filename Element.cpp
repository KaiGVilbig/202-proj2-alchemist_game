#include "Element.h" 
#include <iostream>
#include <string>
#include <cstdlib>
#include <iomanip>
using namespace std;

//Default constructor
Element::Element() {

} 
Element::Element(string name, string element1, string element2) {
	m_name = name; //Name of this element
	m_element1 = element1; //Name of first required element to create
	m_element2 = element2; //Name of second required element to create
}
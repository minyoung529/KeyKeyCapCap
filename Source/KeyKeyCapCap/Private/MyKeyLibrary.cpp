// Fill out your copyright notice in the Description page of Project Settings.


#include "MyKeyLibrary.h"

unordered_map<int, const char*> MyKeyLibrary::keyMap = unordered_map<int, const char*>();
unordered_map<int, const char*> MyKeyLibrary::meshKeyMap = unordered_map<int, const char*>();;

MyKeyLibrary::MyKeyLibrary()
{

}

MyKeyLibrary::~MyKeyLibrary()
{
}

void MyKeyLibrary::SetKeyMap()
{
#pragma region  Alphabet
	keyMap[(int)KEY_TYPE::A] = "A";
	keyMap[(int)KEY_TYPE::B] = "B";
	keyMap[(int)KEY_TYPE::C] = "C";
	keyMap[(int)KEY_TYPE::D] = "D";
	keyMap[(int)KEY_TYPE::E] = "E";
	keyMap[(int)KEY_TYPE::F] = "F";
	keyMap[(int)KEY_TYPE::G] = "G";
	keyMap[(int)KEY_TYPE::H] = "H";
	keyMap[(int)KEY_TYPE::I] = "I";
	keyMap[(int)KEY_TYPE::J] = "J";
	keyMap[(int)KEY_TYPE::K] = "K";
	keyMap[(int)KEY_TYPE::L] = "L";
	keyMap[(int)KEY_TYPE::M] = "M";
	keyMap[(int)KEY_TYPE::N] = "N";
	keyMap[(int)KEY_TYPE::O] = "O";
	keyMap[(int)KEY_TYPE::P] = "P";
	keyMap[(int)KEY_TYPE::Q] = "Q";
	keyMap[(int)KEY_TYPE::R] = "R";
	keyMap[(int)KEY_TYPE::S] = "S";
	keyMap[(int)KEY_TYPE::T] = "T";
	keyMap[(int)KEY_TYPE::U] = "U";
	keyMap[(int)KEY_TYPE::V] = "V";
	keyMap[(int)KEY_TYPE::W] = "W";
	keyMap[(int)KEY_TYPE::X] = "X";
	keyMap[(int)KEY_TYPE::Y] = "Y";
	keyMap[(int)KEY_TYPE::Z] = "Z";
#pragma endregion

#pragma region Number
	keyMap[(int)KEY_TYPE::Zero] = "Zero";
	keyMap[(int)KEY_TYPE::One] = "One";
	keyMap[(int)KEY_TYPE::Two] = "Two";
	keyMap[(int)KEY_TYPE::Three] = "Three";
	keyMap[(int)KEY_TYPE::Four] = "Four";
	keyMap[(int)KEY_TYPE::Five] = "Five";
	keyMap[(int)KEY_TYPE::Six] = "Six";
	keyMap[(int)KEY_TYPE::Seven] = "Seven";
	keyMap[(int)KEY_TYPE::Eight] = "Eight";
	keyMap[(int)KEY_TYPE::Nine] = "Nine";
#pragma endregion

#pragma region Other
	keyMap[(int)KEY_TYPE::Tab] = "Tab";
	keyMap[(int)KEY_TYPE::Enter] = "Enter";
	keyMap[(int)KEY_TYPE::Space] = "SpaceBar";
	keyMap[(int)KEY_TYPE::Shift] = "RightShift";
#pragma endregion
}

void MyKeyLibrary::SetMeshKeyMap()
{
#pragma region Alphabets
	meshKeyMap[(int)KEY_TYPE::A] = "A";
	meshKeyMap[(int)KEY_TYPE::B] = "B";
	meshKeyMap[(int)KEY_TYPE::C] = "C";
	meshKeyMap[(int)KEY_TYPE::D] = "D";
	meshKeyMap[(int)KEY_TYPE::E] = "E";
	meshKeyMap[(int)KEY_TYPE::F] = "F";
	meshKeyMap[(int)KEY_TYPE::G] = "G";
	meshKeyMap[(int)KEY_TYPE::H] = "H";
	meshKeyMap[(int)KEY_TYPE::I] = "I";
	meshKeyMap[(int)KEY_TYPE::J] = "J";
	meshKeyMap[(int)KEY_TYPE::K] = "K";
	meshKeyMap[(int)KEY_TYPE::L] = "L";
	meshKeyMap[(int)KEY_TYPE::M] = "M";
	meshKeyMap[(int)KEY_TYPE::N] = "N";
	meshKeyMap[(int)KEY_TYPE::O] = "O";
	meshKeyMap[(int)KEY_TYPE::P] = "P";
	meshKeyMap[(int)KEY_TYPE::Q] = "Q";
	meshKeyMap[(int)KEY_TYPE::R] = "R";
	meshKeyMap[(int)KEY_TYPE::S] = "S";
	meshKeyMap[(int)KEY_TYPE::T] = "T";
	meshKeyMap[(int)KEY_TYPE::U] = "U";
	meshKeyMap[(int)KEY_TYPE::V] = "V";
	meshKeyMap[(int)KEY_TYPE::W] = "W";
	meshKeyMap[(int)KEY_TYPE::X] = "X";
	meshKeyMap[(int)KEY_TYPE::Y] = "Y";
	meshKeyMap[(int)KEY_TYPE::Z] = "Z";
#pragma endregion

#pragma region Number
	meshKeyMap[(int)KEY_TYPE::Zero] = "0";
	meshKeyMap[(int)KEY_TYPE::One] = "1";
	meshKeyMap[(int)KEY_TYPE::Two] = "2";
	meshKeyMap[(int)KEY_TYPE::Three] = "3";
	meshKeyMap[(int)KEY_TYPE::Four] = "4";
	meshKeyMap[(int)KEY_TYPE::Five] = "5";
	meshKeyMap[(int)KEY_TYPE::Six] = "6";
	meshKeyMap[(int)KEY_TYPE::Seven] = "7";
	meshKeyMap[(int)KEY_TYPE::Eight] = "8";
	meshKeyMap[(int)KEY_TYPE::Nine] = "9";
#pragma endregion

	meshKeyMap[(int)KEY_TYPE::Tab] = "Tab";
	meshKeyMap[(int)KEY_TYPE::Enter] = "Enter";
	meshKeyMap[(int)KEY_TYPE::Space] = "Space";
	meshKeyMap[(int)KEY_TYPE::Shift] = "Shift";
	meshKeyMap[(int)KEY_TYPE::Shift] = "Shift";
}
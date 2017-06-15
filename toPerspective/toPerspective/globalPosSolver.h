#pragma once

#ifndef GLOBALPOSSOLVER_H
#define GLOBALPOSSOLVER_H

#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include "objStruct.h"

using namespace std;
using namespace cv;

class globalPosSolver {
public:
	globalPosSolver() {};
	globalPosSolver(int numCam, int numId):numCam(numCam), numId(numId), NextCamIdx(0){
		globalObjList = NULL;
		localObjList = new obj*[numCam];
	}

	~globalPosSolver() {
		delete [] localObjList;
		localObjList = NULL;

		obj* p;
		obj* pNext;

		while (globalObjList) {
			if (globalObjList->next == NULL) {
				delete globalObjList;
				globalObjList = NULL;
				return;
			}
		
			p = globalObjList;
			pNext = p->next;
			while (pNext->next) {
				p = pNext;
				pNext = pNext->next;
			}

			p->next = NULL;
			delete pNext;
		}
	}

	void setNumCam(int numCam);
	void setNumId(int numId);

	void addLocalObjList(obj* objList);
	void process();
	obj* getGlocalObjList();
	
private : 
	obj* findObj(obj* objList, int id);
	void addGlobalObj(obj* newGolobalObj);

	int numCam = -1;
	int NextCamIdx = 0;
	int numId = -1;
	obj** localObjList;
	obj* globalObjList;
};

#endif
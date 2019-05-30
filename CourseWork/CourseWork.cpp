#include "pch.h"
#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>





using namespace std;



struct Product {
	Product *next;
	
	
	int productId;
	int deadline;
	int amount;
	int *equipmentClass = new int[10]; 
	int cof = 0;


};

Product *firstElementProduct;
Product *secondElementProduct;
Product *lastElementProduct;

struct Equipment {
	Equipment *next;

	int equipmentID;
	int speedPerHour;
	int time = 1552867200;



};

Equipment *firstElementEquipment;
Equipment *lastElementEquipment;

struct plan {
	int productId;
	int equipmentID;
	int timeStart;
	int timeFinish;
	int count = 0;
	plan *next;
};

plan *firstElementPlan;
plan *lastElementPlan;

struct jsonBlock {
	char *A = new char[100];
	char *B = new char[100];
	char *C = new char[100];
	char *D = new char[100];
	jsonBlock *next;
};
jsonBlock *firstElementJsonBlock;
jsonBlock *lastElementJsonBlock;


Product * mergeListsProduct(Product * a, Product * b) {

	Product tmp;
	Product * head = &tmp;
	Product * c = head;

	// Сливаем

	while ((a != 0) && (b != 0)) {
		
		if (a->cof < b->cof ) { 
			c->next = a;
			c = a;
			a = a->next;
		}
		else {
			c->next = b;
			c = b;
			b = b->next;
		}
	}

	// Присоединяем оставшийся "хвост"

	c->next = (a == 0) ? b : a;


	return head->next;
}

Product * mergeSortProduct(Product * c) {

	if (c == 0 || c->next == 0) { // сортировать нечего
		return c;
	}

	Product * a = c; // a хранит начало первой части
	Product * b = c->next; // служебный указатель

	while ((b != 0) && (b->next != 0)) {
		c = c->next; // первый указатель делает один шаг
		b = b->next->next; // второй - два шагa
	}

	b = c->next; // в b записали начало второй части списка

	c->next = 0; // разрываем связь - конец первой части списка


	// Рекурсивно вызываем ту же процедуру и сливаем части списка

	return mergeListsProduct(mergeSortProduct(a), mergeSortProduct(b));

}



Equipment * mergeListsEquipment(Equipment * a, Equipment * b) {

	Equipment tmp;
	Equipment * head = &tmp;
	Equipment * c = head;

	

	while ((a != 0) && (b != 0)) {
		
		if (a->speedPerHour < b->speedPerHour) {
			c->next = a;
			c = a;
			a = a->next;
		}
		else {
			c->next = b;
			c = b;
			b = b->next;
		}
	}


	c->next = (a == 0) ? b : a;


	return head->next;
}

Equipment * mergeSortEquipment(Equipment * c) {

	if (c == 0 || c->next == 0) { 
		return c;
	}

	Equipment * a = c; 
	Equipment * b = c->next; 

	while ((b != 0) && (b->next != 0)) {
		c = c->next; 
		b = b->next->next; 
	}

	b = c->next; 

	c->next = 0; 


	

	return mergeListsEquipment(mergeSortEquipment(a), mergeSortEquipment(b));

}


void Cof() {
	Product *temp = new Product;
	temp = firstElementProduct;

	while (temp) {
		int cof;
		if (!temp) {

		}
		cof = temp->deadline / temp->amount;
		//cof = 1;

		temp->cof = cof;
		if (temp->next == NULL) {
			return;
		}
		temp = temp->next;
		
	}
}


void AddElemenToListEquipment(int speedPerHour, int equipmentID)
{
	Equipment *Element = new Equipment;
	Equipment *temp = new Equipment;
	Element->speedPerHour = speedPerHour;
	Element->equipmentID = equipmentID;

	if (firstElementEquipment == NULL && firstElementEquipment == lastElementEquipment) {
		firstElementEquipment = Element;
		lastElementEquipment = Element;
		lastElementEquipment->next = NULL;
	}
	else {
		lastElementEquipment->next = Element;
		temp = lastElementEquipment;
		lastElementEquipment = Element;
		lastElementEquipment->next = NULL;
	}


}

void AddElemenToListJsonEquipment(char A[], char B[], char C[], char D[], int lenghtA, int lenghtB, int lenghtC, int lenghtD ){
	
	int speedPerHour = 0;
	int equipmentID = 0;
	for (int i = 0; i < lenghtD; i++) {
		speedPerHour = 10 * speedPerHour + (D[i] - '0');
	}
	for (int i = 0; i < lenghtB; i++) {
		equipmentID = 10 * equipmentID + (B[i] - '0');
	}

	/*cout << speedPerHour << " " << equipmentID << endl;
	system("pause");*/

	AddElemenToListEquipment(speedPerHour, equipmentID);

}




void AddElemenToListProduct(int deadline, int amount, int IdProd)
{
	Product *Element = new Product;
	Product *temp = new Product;
	Element->amount = amount;
	Element->deadline = deadline;
	Element->cof= deadline / amount;
	Element->productId = IdProd;
	//Element->productId = productId;
	//Element->equipmentClass = equipmentClass;

	if (firstElementProduct == NULL && firstElementProduct == lastElementProduct) {
		firstElementProduct = Element;
		lastElementProduct = Element;
		lastElementProduct->next = NULL;
	}
	else {
		lastElementProduct->next = Element;
		temp = lastElementProduct;
		lastElementProduct = Element;
		lastElementProduct->next = NULL;
	}


}

void AddElemenToListJsonOrder(char A[], char B[], char C[], char D[], int lenghtA, int lenghtB, int lenghtC, int lenghtD) {

	int deadline = 0;
	int amount = 0;
	int IdProd = 0;
	for (int i = 0; i < lenghtD; i++) {
		deadline = 10 * deadline + (D[i] - '0');
	}
	for (int i = 0; i < lenghtC; i++) {
		amount = 10 * amount + (C[i] - '0');
	}
	for (int i = 0; i < lenghtB; i++) {
		IdProd = 10 * IdProd + (B[i] - '0');
	}

	//cout << B;
	//system("pause");

	AddElemenToListProduct(deadline, amount, IdProd);

}

void AddElemenToListJsonProduct(char A[], char B[], char C[], char D[], int lenghtA, int lenghtB, int lenghtC, int lenghtD) {
	int productId = 0;
	int idEq = 0, j = 0;
	for (int i = 0; i < lenghtA; i++) {
		productId = 10 * productId + (A[i] - '0');
	}

	int *equipmentClass = new int[10];
	for (int i = 0; i < 10; i++) {
		equipmentClass[i] = 0;
	}



	for (int i = 0; i < lenghtB; i++) {
		if (B[i] == ',') {
			//cout << idEq << endl;
			equipmentClass[j] = idEq;
			j++;
			idEq = 0;
		}
		else {
			idEq = 10 * idEq + (B[i] - '0');
		}
		
	}
	equipmentClass[j] = idEq;

	Product *temp = new Product;
	temp = firstElementProduct;

	while (temp) {
		if (temp->productId == productId) {
			temp->equipmentClass = equipmentClass;
		}
		temp = temp->next;
	}




}






void AddElemenToListPlan(int productId, int equipmentID, int timeStart, int timeFinish, int count)
{
	plan *Element = new plan;
	plan *temp = new plan;
	Element->productId = productId;
	Element->equipmentID = equipmentID;
	Element->timeStart = timeStart;
	Element->timeFinish = timeFinish;
	Element->count = count;

	if (firstElementPlan == NULL && firstElementPlan == lastElementPlan) {
		firstElementPlan = Element;
		lastElementPlan = Element;
		lastElementPlan->next = NULL;
	}
	else {
		lastElementPlan->next = Element;
		temp = lastElementPlan;
		lastElementPlan = Element;
		lastElementPlan->next = NULL;
	}


}

Equipment * searchEquipment(Product * temp1) {
	Equipment *temp = new Equipment;
	//Product *temp1 = new Product;
	//temp1 = firstElementProduct;
	temp = firstElementEquipment;
	


	while (temp) {
		for (int i = 0; i < 10; i++) {
			if (temp->equipmentID == temp1->equipmentClass[i]) {
				return temp;
			}
		
		}

		temp = temp->next;
	}

	return temp;
}





////////////////////////////////////////////////////////////////
void ShowSingleLinkedListProduct() {
	Product *temp = new Product;
	temp = firstElementProduct;

	while (temp) {
		cout << temp->deadline << " " << temp->amount << " " << temp->productId << " " << temp->cof; //" " << temp->cof ;
		//cout << temp->deadline << " " << temp->amount << " " << temp->productId;
		
		for (int i = 0; i < 10; i++) {
			cout << temp->equipmentClass[i] << " ";
		}
		//cout << endl;
		temp = temp->next;
		cout << endl;
		//system("pause");
	}
}

void ShowSingleLinkedList(){
	
	Equipment *temp = new Equipment;
	temp = firstElementEquipment;

	while (temp) {
		cout << temp->speedPerHour << " " << temp->equipmentID << endl;;
		temp = temp->next;
	}
}

void ShowSingleLinkedListPlan() {
	plan *temp = new plan;
	temp = firstElementPlan;

	while (temp) {
		cout << temp->productId << " " << temp->equipmentID << " " << temp->timeStart << " " << temp->timeFinish << " " << temp->count << endl;
		/*if (temp->timeStart == 0 && temp->equipmentID == 14) {
			system("pause");
		}*/
		temp = temp->next;
	}
}

void ShowSingleLinkedListJsonBlock() {
	jsonBlock *temp = new jsonBlock;
	temp = firstElementJsonBlock;

	while (temp) {
		cout << temp->A << " " << temp->B << " " << temp->C << temp->D << endl;
		temp = temp->next;
	}
}

///////////////////////////////////////////////////////////////////




void createPlan() {
	
	while (secondElementProduct != NULL){
		Equipment *temp = new Equipment;
		Product *temp2 = new Product;
		Product *temp3 = new Product;
		plan *temp1 = new plan;


		temp3 = secondElementProduct;
		int productId = temp3->productId;
		int amount = temp3->amount;
		
		
		temp = searchEquipment(secondElementProduct);
		
		
		int timeOneProduct = 3600 / temp->speedPerHour;

			

		AddElemenToListPlan(productId, temp->equipmentID, temp->time, timeOneProduct * amount + temp->time, amount);

		temp->time = timeOneProduct * amount + temp->time;
		secondElementProduct = secondElementProduct->next;
		//temp2 = secondElementProduct->next;
		//delete temp2;
		


		//secondElementProduct = secondElementProduct->next;

		//cout << productId << " " <<  temp->equipmentID << " " <<  temp->time << " " << timeOneProduct * amount + temp->time << " " <<  amount;
	
		//system("pause");
	}



}

void compressionPlan() {
	plan *temp = new plan;
	temp = firstElementPlan;

	

	while (temp) {
		
		if (temp->next != NULL) {
			if(temp->equipmentID == temp->next->equipmentID && temp->productId == temp->next->productId && temp) {
				temp->timeFinish = temp->timeFinish + temp->next->timeFinish - temp->next->timeStart;
				temp->count = temp->count + temp->next->count;
				temp->next = temp->next->next;
				
			}
		}
		

		temp = temp->next;
	}


}

void compressionStart() {
	plan *temp = new plan;
	temp = firstElementPlan;
	int k = 0, max = 0;
	while (temp) {

		if (temp->next != NULL) {
			if (temp->equipmentID == temp->next->equipmentID && temp->productId == temp->next->productId && temp) {
				k++;

			}
			else {
				if (max < k) {
					max = k;
				}
				k = 0;
			}
		}
		
		temp = temp->next;
	}
	for (int i = 0; i < max; i++) {
		compressionPlan();
	}



}




///////////////////////////////////////////////
void saFile() {
	plan *temp = new plan;
	temp = firstElementPlan;
	ofstream fout;
	fout.open("DataTest.txt", ios::binary);



	while (temp) {
		fout << temp->equipmentID << "  " << temp->productId << " " << temp->count << " " << temp->timeStart << " " << temp->timeFinish << "\n";
		

		temp = temp->next;
	}

	
}

void sa() {
	plan *temp = new plan;
	temp = firstElementPlan;
	int p1 = 0;
	int p2 = 0;
	int p3 = 0;
	int p4 = 0;
	int p5 = 0;
	int p6 = 0;
	


	while (temp) {
		if (temp->productId == 1) {
			p1 += temp->count;
		}
		if (temp->productId == 2) {
			p2 += temp->count;
		}
		if (temp->productId == 3) {
			p3 += temp->count;
		}
		if (temp->productId == 4) {
			p4 += temp->count;
		}
		if (temp->productId == 5) {
			p5 += temp->count;
		}
		if (temp->productId == 6) {
			p6 += temp->count;
		}



		temp = temp->next;
	}



	cout << p1 << endl;
	cout << p2 << endl;
	cout << p3 << endl;
	cout << p4 << endl;
	cout << p5 << endl;
	cout << p6 << endl;


}

void checkDeadline() {
	
	Product *temp;
	temp = firstElementProduct;
	int count = 0, timeFin;
	while (temp) {
		system("pause");
		plan *tempPlan;
		tempPlan = firstElementPlan;
		while (tempPlan) {
			if (temp->productId == tempPlan->productId) {
				count += tempPlan->count;
				timeFin = tempPlan->timeFinish;
			}
			tempPlan = tempPlan->next;
		}
		if (count > temp->amount) {
			if (timeFin >= temp->deadline) {
				system("pause");
			}
			else {
				cout << "NO" << temp->productId;
			}

		}
		//cout << count;
		//system("pause");

		temp = temp->next;
	}

}

////////////////////////////////////////////////////////



void readJsonEquipment() {
	int coun = 0;

	
	ifstream i_File; 

	i_File.open("C:\\Users\\Kirill\\source\\repos\\CourseWork\\DataSet\\equipment.json", ios::binary); // Открыли файл

	if (!i_File.is_open()) // Проверили, удалось ли открыть файл
	{
		cout << "Открыть файл не удалось! \n";
		return;
	}

	int valueReading = false;
	char *A = new char[100];
	char *B = new char[100];
	char *C = new char[100];
	char *D = new char[100];
	int lengthA = 0, lengthB = 0, lengthC = 0, lengthD = 0;
	
	int fieldReading = false;
	char fieldName;
	bool fieldNameAlreadyRead = false;

	char currentChar[1];
	currentChar[0] = 'x';
	int blockDataLength = 0;

	bool blockReading = false;
	while (i_File) {
		if (valueReading) {
			if (currentChar[0] == '"') {
				fieldNameAlreadyRead = false;
				valueReading = false;
			} else {
				if (fieldName == 'A') {
					A[lengthA] = currentChar[0];
					lengthA++;
				}
				if (fieldName == 'B') {
					B[lengthB] = currentChar[0];
					lengthB++;
				}
				if (fieldName == 'C') {
					C[lengthC] = currentChar[0];
					lengthC++;
				}
				if (fieldName == 'D') {
					D[lengthD] = currentChar[0];
					lengthD++;
				}
			}
		} else if (fieldReading) {
			if (currentChar[0] == '"') {
				fieldReading = false;
				fieldNameAlreadyRead = true;
			}
			else {
				fieldName = currentChar[0];
			}
		} else if (!blockReading && currentChar[0] == '{') {
			blockDataLength = 0;
			blockReading = true;
			valueReading = false;
			fieldReading = false;
			fieldNameAlreadyRead = false;
			lengthA = 0;
			lengthB = 0;
			lengthC = 0;
			lengthD = 0;
			
		} else if (blockReading && currentChar[0] == '}') {
			blockReading = false;
			AddElemenToListJsonEquipment(A, B, C, D, lengthA, lengthB, lengthC, lengthD);
			/*cout << A << endl;
			cout << B << endl;
			cout << C << endl;
			cout << D << endl;
			system("pause");*/
		} else if (blockReading && currentChar[0] == '"') {
			if (fieldNameAlreadyRead) {
				valueReading = true;
			} else {
				fieldReading = true;
			}
		} else {
			//cout << currentChar[0] << "\n";
		}

		i_File.read((char *)currentChar, sizeof(currentChar));

		coun++;
		/*if (coun == 100) {
			break;
		}*/
	}
		
	
	//ShowSingleLinkedListJsonBlock();
	i_File.close(); // Закрываем файл

	
	
	

}

void readJsonOrder() {
	int coun = 0;


	ifstream i_File;

	i_File.open("C:\\Users\\Kirill\\source\\repos\\CourseWork\\DataSet\\order.json", ios::binary); // Открыли файл

	if (!i_File.is_open()) // Проверили, удалось ли открыть файл
	{
		cout << "Открыть файл не удалось! \n";
		return;
	}

	int valueReading = false;
	char *A = new char[100];
	char *B = new char[100];
	char *C = new char[100];
	char *D = new char[100];
	int lengthA = 0, lengthB = 0, lengthC = 0, lengthD = 0;

	int fieldReading = false;
	char fieldName;
	bool fieldNameAlreadyRead = false;

	char currentChar[1];
	currentChar[0] = 'x';
	int blockDataLength = 0;

	bool blockReading = false;
	while (i_File) {
		if (valueReading) {
			if (currentChar[0] == '"') {
				fieldNameAlreadyRead = false;
				valueReading = false;
			}
			else {
				if (fieldName == 'A') {
					A[lengthA] = currentChar[0];
					lengthA++;
				}
				if (fieldName == 'B') {
					B[lengthB] = currentChar[0];
					lengthB++;
				}
				if (fieldName == 'C') {
					C[lengthC] = currentChar[0];
					lengthC++;
				}
				if (fieldName == 'D') {
					D[lengthD] = currentChar[0];
					lengthD++;
				}
			}
		}
		else if (fieldReading) {
			if (currentChar[0] == '"') {
				fieldReading = false;
				fieldNameAlreadyRead = true;
			}
			else {
				fieldName = currentChar[0];
			}
		}
		else if (!blockReading && currentChar[0] == '{') {
			blockDataLength = 0;
			blockReading = true;
			valueReading = false;
			fieldReading = false;
			fieldNameAlreadyRead = false;
			lengthA = 0;
			lengthB = 0;
			lengthC = 0;
			lengthD = 0;

		}
		else if (blockReading && currentChar[0] == '}') {
			blockReading = false;
			AddElemenToListJsonOrder(A, B, C, D, lengthA, lengthB, lengthC, lengthD);
			/*cout << A << endl;
			cout << B << endl;
			cout << C << endl;
			cout << D << endl;
			system("pause");*/
		}
		else if (blockReading && currentChar[0] == '"') {
			if (fieldNameAlreadyRead) {
				valueReading = true;
			}
			else {
				fieldReading = true;
			}
		}
		else {
			//cout << currentChar[0] << "\n";
		}

		i_File.read((char *)currentChar, sizeof(currentChar));

		coun++;
		/*if (coun == 100) {
			break;
		}*/
	}


	//ShowSingleLinkedListJsonBlock();
	i_File.close(); // Закрываем файл





}

void readJsonProduct() {
	int coun = 0;


	ifstream i_File;

	i_File.open("C:\\Users\\Kirill\\source\\repos\\CourseWork\\DataSet\\product.json", ios::binary); // Открыли файл

	if (!i_File.is_open()) // Проверили, удалось ли открыть файл
	{
		cout << "Открыть файл не удалось! \n";
		return;
	}

	int valueReading = false;
	char *A = new char[100];
	char *B = new char[100];
	char *C = new char[100];
	char *D = new char[100];
	int lengthA = 0, lengthB = 0, lengthC = 0, lengthD = 0;

	int fieldReading = false;
	char fieldName;
	bool fieldNameAlreadyRead = false;

	char currentChar[1];
	currentChar[0] = 'x';
	int blockDataLength = 0;

	bool blockReading = false;
	while (i_File) {
		if (valueReading) {
			if (currentChar[0] == '"') {
				fieldNameAlreadyRead = false;
				valueReading = false;
			}
			else {
				if (fieldName == 'A') {
					A[lengthA] = currentChar[0];
					lengthA++;
				}
				if (fieldName == 'B') {
					B[lengthB] = currentChar[0];
					lengthB++;
				}
				if (fieldName == 'C') {
					C[lengthC] = currentChar[0];
					lengthC++;
				}
				if (fieldName == 'D') {
					D[lengthD] = currentChar[0];
					lengthD++;
				}
			}
		}
		else if (fieldReading) {
			if (currentChar[0] == '"') {
				fieldReading = false;
				fieldNameAlreadyRead = true;
			}
			else {
				fieldName = currentChar[0];
			}
		}
		else if (!blockReading && currentChar[0] == '{') {
			blockDataLength = 0;
			blockReading = true;
			valueReading = false;
			fieldReading = false;
			fieldNameAlreadyRead = false;
			lengthA = 0;
			lengthB = 0;
			lengthC = 0;
			lengthD = 0;

		}
		else if (blockReading && currentChar[0] == '}') {
			blockReading = false;
			AddElemenToListJsonProduct(A, B, C, D, lengthA, lengthB, lengthC, lengthD);
			/*cout << A << endl;
			cout << B << endl;
			cout << C << endl;
			cout << D << endl;
			system("pause");*/
		}
		else if (blockReading && currentChar[0] == '"') {
			if (fieldNameAlreadyRead) {
				valueReading = true;
			}
			else {
				fieldReading = true;
			}
		}
		else {
			//cout << currentChar[0] << "\n";
		}

		i_File.read((char *)currentChar, sizeof(currentChar));

		coun++;
		/*if (coun == 100) {
			break;
		}*/
	}


	//ShowSingleLinkedListJsonBlock();
	i_File.close(); // Закрываем файл





}



	

	
	
	



















int main() {

	int mas0[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	AddElemenToListProduct(1, 1, 1);
	firstElementProduct->equipmentClass = mas0;
	AddElemenToListEquipment(1, 0);



	readJsonOrder();
	readJsonProduct();
	readJsonEquipment();
	//ShowSingleLinkedListProduct();
	
	//Cof();

	mergeSortProduct(firstElementProduct);
	secondElementProduct = firstElementProduct->next;
	//ShowSingleLinkedListProduct();
	mergeSortEquipment(firstElementEquipment);
	
	firstElementEquipment = firstElementEquipment->next;
	//ShowSingleLinkedList();
	//system("pause");
	createPlan();
	ShowSingleLinkedListPlan();
	//compressionStart();
	//saFile();
	//sa();
	




	//ShowSingleLinkedListProduct();
	

	
	//ShowSingleLinkedList();
	
	/*int mas0[] = { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };
	int mas1[] = { 1, 4, 7, 2, 0, 0, 0, 0, 0, 0 };
	int mas2[] = { 5, 7, 2, 9, 18, 6, 0, 0, 0, 0 };
	int mas3[] = { 1, 9, 11, 45, 0, 0, 0, 0, 0, 0 };
	int mas4[] = { 2, 11, 4, 12, 0, 0, 0, 8, 0, 0 };
	int mas5[] = { 0, 7, 71, 14, 19, 0, 0, 0, 0, 0 };
	int mas6[] = { 9, 5, 7, 2, 0, 0, 0, 0, 0, 0 };

	AddElemenToListProduct(0, 1, 0, mas0);
	AddElemenToListProduct(1209600, 600, 1, mas1);
	AddElemenToListProduct(1296460, 450, 2, mas2);
	AddElemenToListProduct(1276000, 120, 3, mas3);
	AddElemenToListProduct(1253600, 780, 4, mas4);
	AddElemenToListProduct(1206400, 800, 5, mas5);
	AddElemenToListProduct(1227800, 100, 6, mas6);



	AddElemenToListEquipment(1, 0);
	AddElemenToListEquipment(9, 4);
	AddElemenToListEquipment(13, 7);
	AddElemenToListEquipment(79, 2);
	AddElemenToListEquipment(11, 5);
	AddElemenToListEquipment(17, 9);
	AddElemenToListEquipment(2, 18);
	AddElemenToListEquipment(3, 6);
	AddElemenToListEquipment(9, 11);
	AddElemenToListEquipment(15, 45);
	AddElemenToListEquipment(156, 12);
	AddElemenToListEquipment(8, 71);
	AddElemenToListEquipment(7, 14);
	AddElemenToListEquipment(9, 19);
	






	Cof();
	mergeSortProduct(firstElementProduct);
	secondElementProduct = firstElementProduct->next;
	mergeSortEquipment(firstElementEquipment);
	createPlan();
	compressionStart();


	//checkDeadline();

	saFile();
	//ShowSingleLinkedListPlan();
	sa();
	//ShowSingleLinkedListProduct();
	//cout << endl;
	//ShowSingleLinkedList();
	*/


	return 0;
}



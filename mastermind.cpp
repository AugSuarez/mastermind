#include <iostream>
#include <stdexcept>
#include <vector>

constexpr int numberOfSlots=4;

constexpr int maxTurns=10;

constexpr int numOfColors=5; //5=red,blue,orange,yellow,green
	
	int slotAnswer;

	std::vector<std::string> hintVector;

 // -----------------------------------------------------------printVector----------------------------------------------------


template <typename T>
void printVector(std::vector<T> &myVector){
	for (int i = 0; i < myVector.size(); ++i){
		std::cout << myVector[i] << " ";
	}
}

 // -----------------------------------------------------------clearVector----------------------------------------------------


template <typename T>
void clearVector(std::vector<T> &myVector){
	for (int i = 0; i < numberOfSlots; ++i){
		myVector.pop_back();
	}
}

 // -----------------------------------------------------------printHintVector----------------------------------------------------


template <typename T>
void printHintVector(std::vector<T> myVector){
	std::cout << "         ";
	for (int i = 0; i < numberOfSlots; ++i){
		if(myVector[i]=="black"){
			std::cout << myVector[i] << " ";
		}
	}
	for (int i = 0; i < numberOfSlots; ++i){
		if(myVector[i]=="white"){
			std::cout << myVector[i] << " ";
		}
	}
	for (int i = 0; i < numberOfSlots; ++i){
		if(myVector[i]=="empty"){
			std::cout << myVector[i] << " ";
		}
	}
}

 // ---------------------------------------------------------toLowerFunction----------------------------------------------------
std::string toLowerFunction(std::string &myString){
	for(auto &c: myString){c=tolower(c);}
	return myString;
}


 // -----------------------------------------------------------emptyVector----------------------------------------------------

template <typename T>
void emptyVector(std::vector<T> &myVector){
	for (int i = 0; i < numberOfSlots; ++i){
		myVector.push_back("empty");
	}
}

 // -----------------------------------------------------------checKUserInput----------------------------------------------------


std::string checkUserInput(std::string &userInput){

	std::string colorArray[5][5]={{"red","blue","orange","yellow","green"}, {"r","b","o","y","g"}};

	for(int i=0; i<5; i++){
		if(toLowerFunction(userInput)==colorArray[0][i] || toLowerFunction(userInput)==colorArray[1][i]){return colorArray[0][i];}
	}
	//investigar arreglo asociativo c++
		throw std::runtime_error("Invalid Color!");
}	


/*char getFirstLetter(std::string &myString)

	'v' 'e' 

	return [0];*/

 // -----------------------------------------------------------fillVector----------------------------------------------------

void fillVector(std::vector<std::string> &myVector){
	for (int i=0; i < numberOfSlots; ++i)//start of for loop to assign colors to the slots
		{
			int slotAnswer=(rand()%numOfColors + 1);
			if(slotAnswer==1){myVector.push_back("red");}
			else if(slotAnswer==2){myVector.push_back("blue");}
			else if(slotAnswer==3){myVector.push_back("orange");}
			else if(slotAnswer==4){myVector.push_back("yellow");}
			else if(slotAnswer==5){myVector.push_back("green");}
		}
}

 // -----------------------------------------------------------deleteColor----------------------------------------------------

bool deleteColor(std::string &myColor, std::vector<std::string> &myVector){
	bool status=false;
	std::vector<std::string> copiedTargetVector=myVector;
	std::vector<std::string>& copiedTargetVectorReference=copiedTargetVector;
	for (int i = 0; i < myVector.size(); ++i){
		if(myColor==myVector[i] && status==false){
			copiedTargetVectorReference[i]="0";
			status=true;
		}
	}
	copiedTargetVector=myVector;
	return status;
}
 // -----------------------------------------------------------checKResult----------------------------------------------------

void checkResult(std::vector<std::string> &myVector,std::vector<std::string> &myVector2){//guessVector, targetVector

	for (int i = 0; i < myVector.size(); ++i){
		if (myVector[i]==myVector2[i]){
			hintVector[i]="black";
		}
	}

	for (int i = 0; i < myVector.size(); ++i){
		for (int x = 0; x < myVector2.size(); ++x){
			if (myVector[i]==myVector2[x] && hintVector[i]=="empty"  && hintVector[x]!="black" && deleteColor(myVector[i],myVector2)==true){
				hintVector[i]="white";
			}
			//std::cout << "hintVector["<<i<<"] " << hintVector[i] << std::endl;
		}
	}
}


//int integerUserInput;

int main (){ // -----------------------------------------------------------MAIN----------------------------------------------------

	std::vector<std::string> targetVector;

	std::vector<std::string> guessVector;
	
	std::string userInput, guessString;

	srand(time(NULL));

	fillVector(targetVector);

	std::cout << std::endl;

	std::cout << "Mastermind: " << std::endl;

	//printVector(targetVector);//***************************************

	std::cout << std::endl;

	int turnCount=0;

	while(guessVector!=targetVector && turnCount<=maxTurns){

		turnCount++;

		emptyVector(hintVector);

		std::cout << "guess 4 colors: " << std::endl;


		for (int i = 0; i < numberOfSlots; ++i){

			std::cin >> guessString;

			try{
				guessVector.push_back(checkUserInput(guessString));
			}

			catch(std::runtime_error colorError){
				std::cout << "Runtime Error: " << colorError.what();
				return -1;
			}

		}

		checkResult(guessVector, targetVector);

		std::cout << "\n Your guess:";

		printVector(guessVector);

		std::cout << std::endl;
		
		printHintVector(hintVector);

		std::cout << "\n";

		if (guessVector==targetVector){
			std::cout << "You win!";
			return 0;
		}
		
		else{

			//-----------------------------------------------SETUP-NEXT-LEVEL-----------------------------------------------

			clearVector(guessVector);

			clearVector(hintVector);

				if (turnCount==maxTurns){
					std::cout << "You lose!\nThe answer was: ";
					printVector(targetVector);
					return 0;
				}

				else if(turnCount<maxTurns){

					if (turnCount<9){
						std::cout << "\nYou have " << maxTurns-turnCount << " turns left.\n" << std::endl;
					}

				if (turnCount==(maxTurns-1)){
					std::cout << "\nYou have " << maxTurns-turnCount << " turn left.\n" << std::endl;
				}
			}
		}	
	}
	return 0;
}
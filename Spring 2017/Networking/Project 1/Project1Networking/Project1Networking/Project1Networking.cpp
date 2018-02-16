#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
/* EXAMPLE: "topology1.txt"

src dest cost delay
4	1	 532  0.076792222
4	2	 669  0.133467327
3	2	 722  0.051783073
3	4	 196  0.184216793
0	1	 907  0.125563734
0	2	 291  0.217457185
1	3	 24	  0.208844158
*/

// Opens the file and returns true if successful and false if not.
// inputs data from file to fileData array.
bool OpenFile(string,double[100][4],int&);
void SendPeriodicUpdate(struct router RT[100][100], struct router_neighbors RN[100], int lastRouterID);
void ReceiveUpdate(struct router_neighbors RN[100], struct router RT[100][100]);
void SendTriggeredUpdate(struct router RT[100][100], struct router_neighbors RN[100], int sendingRouterID);
void FowardDataPacket(struct router RT[100][100], struct router_neighbors RN[100]);

/*
	Used to create events into linked list called event queue.
*/
struct event
{
	int type;     // 0 = periodic update, 1 = triggered update, 2 = data packet
	float time;   // time = clock + delay
	int src;      // source (from)
	int dest;     // destination (to)
	int cost;     // advertised cost (maybe not needed...)
	int tempTable[100][3]; //tempTable[row of data][{0}destination,{1}cost,{2}NextHop]
	event * next; // pointer to advance event queue 
};
event * eventHead; // head pointer for event queue
/*
	this struct contains the necessary and additional information with each router.
	in main() router struct will be initialized as an array of router structs.
	int destination, cost, and nextHop will be maintained by the fileData[0-n][0-3].
*/
struct router {
	int destination = -1, 
		cost = -1, 
		nextHop = -1;
};

struct router_neighbors {
	vector <int> neighbor;
	vector <double> delay;
};

// Global variables
int simulation_clock = 0;
double convergeTime = 0.0;
int lastConvergedRouterID = -1;
int hopcount = 0;
int convergedHopCount = 0;

int main(int argc, char *argv[])
{
	//string filePath = argv[1];
	string filePath = "topology1.txt";
	//int endTime = (int)argv[2];
	//uintptr_t endTime = reinterpret_cast<uintptr_t>(argv[2]);
	int endTime = 30;
	double fileData[100][4];
	int rows = 0;
	if (!OpenFile(filePath, fileData, rows))
	{
		cout << "\nCorrect the input file name and restart program...\n";
		cout << "Goodbye!\n";
	}
	else
	{
		// Array of Router Structures Routing Table row[newEntry] column[RouterID 0-99]
		router RT[100][100];
		// Array of router_neighbor structures whos index corresponds to the Router ID index
		router_neighbors RN[100];
		/*
			populate routing tables with data from input file.
			create a list of immediate neighbors of each router from this data.
			fileData[row#][0] = source
			fileData[row#][1] = destination
			fileData[row#][2] = cost
			fileData[row#][3] = delay
		*/

		int srcID, destID, cost;
		int lastRouter = 0;
		int i = 0;
		double delay;

		for (int j = 0; j < rows; j++)
		{
			// RT row[newEntry] column[RouterID 0 - 99]
			srcID = fileData[j][0];  // source ID from file.
			destID = fileData[j][1]; // destination ID from file.
			cost = fileData[j][2];   // cost between source and destination from file.
			delay = fileData[j][3];  // delay between source and destination from file.
			// Routing Table population into the RT[newEntry][Router ID(src or dest)] struct
			// from the fileData[row from data][dest,cost,delay]
			// -1 is placed in all data so we know how far to iterate to place new info
			i = 0;
			while (RT[i][srcID].destination != -1)
				i++;
			RT[i][srcID].cost = fileData[j][2];
			RT[i][srcID].destination = RT[i][srcID].nextHop = destID;
			RN[srcID].neighbor.push_back(RT[i][srcID].nextHop);
			RN[srcID].delay.push_back(delay);
			i = 0;
			while (RT[i][destID].destination != -1)
				i++;
			RT[i][destID].cost = fileData[j][2];
			RT[i][destID].destination = RT[i][destID].nextHop = srcID;
			RN[destID].neighbor.push_back(RT[i][destID].nextHop);
			RN[destID].delay.push_back(delay);
			i = 0;
			if (srcID > lastRouter) { lastRouter = srcID; }
			if (destID > lastRouter) { lastRouter = destID; }
		}

		/*
			Scheduling all periodic updates before the while loop.
			Each update will only contain instructions for all nodes to send current
			routing tables AT THAT very moment and place their tables into the event queue.
		*/
		event *newNodePtr;
		for (int k = 0; k <= endTime; k++)
		{
			newNodePtr = new event;
			newNodePtr->time = k;
			newNodePtr->type = 0; // periodic update #
			newNodePtr->next = NULL;
			if (eventHead == NULL)
				eventHead = newNodePtr;
			else
			{
				event *cursor = eventHead;
				while (cursor->next != NULL) // not at last node
					cursor = cursor->next;
				cursor->next = newNodePtr;
			}

		}
		// scheduling 1 data packet event from the correct topology
		event * cursor = eventHead;
		event * previous = cursor;
		newNodePtr = new event;
		newNodePtr->src = 0;
		newNodePtr->type = 3; // data packet type
		newNodePtr->next = NULL;
		
		if (filePath == "topology1.txt") 
		{
			newNodePtr->dest = 3;
			newNodePtr->time = 10;
		}
		if (filePath == "topology2.txt") 
		{
			newNodePtr->dest = 7;
			newNodePtr->time = 20;
		}
		if (filePath == "topology3.txt") 
		{
			newNodePtr->dest = 23;
			newNodePtr->time = 30;
		}
		while (cursor->time < newNodePtr->time)
		{
			previous = cursor;
			cursor = cursor->next;
		}
		// reroute previous->next to the new event and take event's next pointer and point to current.
		previous->next = newNodePtr;
		newNodePtr->next = cursor;
		/*
			main while loop that will host all function calls relating to DV packets,
			event queue, advancing clock with event.time, and taking raw data and
			input into array of structs with Router ID = column index.
		*/
		event * ptr = eventHead;
		while (simulation_clock < endTime)
		{
			ptr = eventHead;
			simulation_clock = eventHead->time;
			hopcount++;
			// Processing of each event
			switch (eventHead->type)
			{
			case 0: // "ALL SEND" Periodic Updates
				SendPeriodicUpdate(RT, RN, lastRouter);
				break;
			case 1: // recieved periodic update
				ReceiveUpdate(RN, RT);
				break;
			case 2: // recieved triggered Update
				ReceiveUpdate(RN, RT);
				break;
			case 3: // recieved data packet
				FowardDataPacket(RT,RN);
				break;
			default:
				cout << "ERROR switch case default...";
				break;
			}
			eventHead = eventHead->next;
			delete ptr;
		}
	}
	return 0;

}

bool OpenFile(string filepath, double fileData[100][4],int& i)
{
	ifstream inputFile;
	inputFile.open(filepath);
	if (inputFile.is_open())
	{
		cout << "File " << filepath << " opened successfully!" << endl;
		i = 0;
		while (inputFile >> fileData[i][0] >> fileData[i][1] >> fileData[i][2] >> fileData[i][3])
		{ i++; }
		inputFile.close();
		return true;
	}
	else
	{
		cout << "ERROR: File " << filepath << " did not open successfully." << endl
			<< "Maybe not in same folder or was misspelt." << endl;
		return false;
	}

}
// This function will process all periodic updates from event queue
void SendPeriodicUpdate(struct router RT[100][100], struct router_neighbors RN[100], int lastRouterID)
{
	/*
		Take eventHead->time
		loop until all routers touched 0-lastRouterID
			find their neighbors
				using: RN[].neighbors
			loop through all routing table rows
				send thier whole packets except those with: neighbor = NextHop.
					using: RT[][]
			add to event queue with time + delay
	*/
	double tempclock = eventHead->time;
	event *newNodePtr;
	int i = 0; // SRC Router ID
	int j = 0; // Neighbor Router Location of ID
	int k = 0; // interator to cycle through the rows of the routers Routing Table.
	while (i <= lastRouterID)
	{
		// reset 'j'.
		j = 0;
		while (j < RN[i].neighbor.size())
		{
			newNodePtr = new event;
			newNodePtr->src = i;
			newNodePtr->dest = RN[i].neighbor.at(j);
			newNodePtr->time = RN[i].delay.at(j) + tempclock;
			newNodePtr->type = 2; // sending out with 2 to indicate these as
								  // receiving periodic update.
			// populate the tempTable with all -1's to indicate as empty values before adding values
			for (int x = 0; x < 100; x++)
			{
				newNodePtr->tempTable[x][0] = -1;
				newNodePtr->tempTable[x][1] = -1;
				newNodePtr->tempTable[x][2] = -1;
			}
			// because the Routing Table of each router has data until a -1 we will loop until then.
			// reset 'k' here.
			k = 0;
			// helper info:
			//	RT[row of data][ID of Router].{destination,cost,nextHop}
			while (RT[k][i].nextHop != -1) // cycle through each row of data until nextHop = -1.
			{
				// assign tempTable[row of data][{0}dest,{1}cost,{2}nextHop,] with RT data
				newNodePtr->tempTable[k][0] = RT[k][i].destination;
				newNodePtr->tempTable[k][1] = RT[k][i].cost;
				newNodePtr->tempTable[k][2] = RT[k][i].nextHop;
				// advance 'k' iterator.
				k++;
			}
			// not necessary but I wanted to initialize it to NULL to be safe.
			newNodePtr->next = NULL;
			// advance cursor and previous until the new event time is greater than the cursor time.
			// at that time we insert the new event so that it is correctly placed in time.
			event *cursor = eventHead;
			event *previous = cursor;
			while (cursor->time < newNodePtr->time)
			{
				previous = cursor;
				cursor = cursor->next;
			}
			// If the previous pointer is still pointing at head ill use eventHead->next
			// in the possibility I am unable to affect the head pointer using previous.
			if (previous == eventHead)
			{
				eventHead->next = newNodePtr;
				newNodePtr->next = cursor;
			}
			// the previous next pointer will point to newNodePtr
			// the newNodePtr next pointer will point to cursor.
			else
			{
				previous->next = newNodePtr;
				newNodePtr->next = cursor;
			}
			// advance 'j' iterator
			j++;
		}
		// advance 'i' iterator
		i++;
	}
}
void ReceiveUpdate(struct router_neighbors RN[100], struct router RT[100][100])
{
	int src = eventHead->src; // who sent the update
	int thisRouter = eventHead->dest; // who it was supposed to go to
	double temptTime = eventHead->time; // record current timestamp
	int i = 0; // iterator for list of neighbors
	int k = 0; // iterator for RoutingTable rows
	int j = 0; // iterator for tempTable rows
	bool exists = false, updated = false;
	//Checking to see if the destination from the eventHead->tempTable exists in Routing Table.
	while (eventHead->tempTable[j][0] != -1)
	{	
		if (eventHead->tempTable[j][2] == thisRouter || eventHead->tempTable[j][0] == thisRouter)
		{
			// if the nextHop or destination is the same ID as the router recieving this
			// update, skip that row of data as per SPLIT HORIZON definition.
			// we dont advertise what we learn from those routers and we dont need to advertise
			// our cost to our neighbor as they already know their cost to ourselves in their own table.
			j++;
		}
		// Helpful info:
		//	 RoutingTable[row of data][thisRouterID] {dest,cost,N.H}
		//	 eventHead "head pointer from eventqueue" ->tempTable[row of data][{0}dest,{1}cost,{2}N.H]
		//	 tempTable is filled with -1's after the data inputed. -1 represents empty field.
		// reset 'k' and "exists" for if statement under while loop.
		k = 0;
		exists = false;
		while (RT[k][thisRouter].destination != -1)
		{
			if (eventHead->tempTable[j][0] == RT[k][thisRouter].destination)
			{
				exists = true;
				if (eventHead->tempTable[j][1] < RT[k][thisRouter].cost)
				{
					RT[k][thisRouter].cost = eventHead->tempTable[j][1];
					RT[k][thisRouter].nextHop = src;
					updated = true;
				}
			}
			// advance 'k' iterator.
			k++;
		}
		// Routing Table did not contain that line of data and will now accept at end of their table.
		if (exists == false)
		{
			// 'k' will be at the next empty row of data to insert into containing all -1's.
			RT[k][thisRouter].destination = eventHead->tempTable[j][0];
			RT[k][thisRouter].cost = eventHead->tempTable[j][1];
			RT[k][thisRouter].nextHop = src;
		}
		j++;
	}
	if (exists == false || updated == true)
	{
		SendTriggeredUpdate(RT,RN,thisRouter);
	}
}

void SendTriggeredUpdate(struct router RT[100][100], struct router_neighbors RN[100], int sendingRouterID)
{
	convergeTime = eventHead->time;
	lastConvergedRouterID = sendingRouterID;
	convergedHopCount = hopcount;
	double tempclock = eventHead->time;
	event *newNodePtr;
	int j = 0; // Neighbor Router index of ID.
	int k = 0; // index interator to cycle through the rows of the routers Routing Table.
	// Only send to your neighbors from the sendingRouterID.
	while (j < RN[sendingRouterID].neighbor.size())
	{
		newNodePtr = new event;
		newNodePtr->src = sendingRouterID;
		newNodePtr->dest = RN[sendingRouterID].neighbor.at(j);
		newNodePtr->time = RN[sendingRouterID].delay.at(j) + tempclock;
		newNodePtr->type = 1; // sending out with 1 to indicate these as
							  // receiving triggered update.
							  // populate the tempTable with all -1's to indicate as empty values before adding values
		for (int x = 0; x < 100; x++)
		{
			newNodePtr->tempTable[x][0] = -1;
			newNodePtr->tempTable[x][1] = -1;
			newNodePtr->tempTable[x][2] = -1;
		}
		// because the Routing Table of each router has data until a -1 we will loop until then.
		// reset 'k' here.
		k = 0;
		// helper info:
		//	RT[row of data][ID of Router].{destination,cost,nextHop}
		while (RT[k][sendingRouterID].nextHop != -1) // cycle through each row of data until nextHop = -1.
		{
			// assign tempTable[row of data][{0}dest,{1}cost,{2}nextHop,] with RT data
			newNodePtr->tempTable[k][0] = RT[k][sendingRouterID].destination;
			newNodePtr->tempTable[k][1] = RT[k][sendingRouterID].cost;
			newNodePtr->tempTable[k][2] = RT[k][sendingRouterID].nextHop;
			// advance 'k' iterator.
			k++;
		}
		// not necessary but I wanted to initialize it to NULL to be safe.
		newNodePtr->next = NULL;
		// advance cursor and previous until the new event time is greater than the cursor time.
		// at that time we insert the new event so that it is correctly placed in time.
		event * cursor = eventHead;
		event * previous = cursor;
		while (cursor->time < newNodePtr->time)
		{
			previous = cursor;
			cursor = cursor->next;
		}
		// If the previous pointer is still pointing at head ill use eventHead->next
		// in the possibility I am unable to affect the head pointer using previous.
		if (previous == eventHead)
		{
			eventHead->next = newNodePtr;
			newNodePtr->next = cursor;
		}
		// the previous next pointer will point to newNodePtr
		// the newNodePtr next pointer will point to cursor.
		else
		{
			previous->next = newNodePtr;
			newNodePtr->next = cursor;
		}
		// advance 'j' iterator
		j++;
	}
	
}
// This function will process all data packets from event queue
void FowardDataPacket(struct router RT[100][100], struct router_neighbors RN[100])
{
	// RT[row of data][{}dest, {}cost, {}nextHop]
	// RN[RouterID].{neighbor}{delay}
	// Topology1.txt: @ time 10, Router 0 recieves a data packet destined to Router 3.
	// Topology2.txt: @ time 20, Router 0 receives a data packet destined to Router 7.
	// Topology3.txt: @ time 30, Router 0 receives a data packet destined to Router 23.
	//                @ eventHead->time  eventHead->src                     eventHead->dest
	int dest = eventHead->dest;
	int src = eventHead->src;
	int i = 0;
	int j = 0;
	if (eventHead->src == eventHead->dest)
	{
		cout << "\nData Packet recieved at Router " << eventHead->dest << "." << endl;
		cout << "At time: " << eventHead->time << "." << endl;
	}
	else
	{
		// loop until we find the location in the Routing table with destination == event destination
		while (RT[i][src].destination != eventHead->dest)
		{
			if (i == 99)
			{
				cout << "Error: destination not found in RoutingTable." << endl;
				return;
			}
				i++;
		}
		// after loop we will have the location of the destination in the Routing Table and where to send
		cout << "I am Router " << src << "." << endl;
		cout << "This packet is destined to Router  " << dest << "." << endl;
		cout << "I am sending this packet to Router  " << RT[i][src].nextHop << "." << endl;
		
		while (j < RN[src].neighbor.size())
		{
			if (RT[i][src].nextHop == RN[src].neighbor.at(j))
			{
				break;
			}
			else
				j++;
		}
		// basically a copy and paste from sendTriggeredUpdate() function.
		event * newNodePtr;
		event * cursor = eventHead;
		event * previous = cursor;
		newNodePtr = new event;
		newNodePtr->src = RT[i][src].nextHop; // src = nextHop so it can we repeated with new RouterID
		newNodePtr->dest = dest;
		newNodePtr->time = RN[src].delay.at(j) + eventHead->time;
		newNodePtr->type = 3; // setting as 3 to continue the data packet.
		// find a location where cursor->time is > newNodePtr->time
		// and fit it between previous and cursor location.
		while (cursor->time < newNodePtr->time)
		{
			previous = cursor;
			cursor = cursor->next;
		}
		// If the previous pointer is still pointing at head ill use eventHead->next
		// in the possibility I am unable to affect the head pointer using previous.
		if (previous == eventHead)
		{
			eventHead->next = newNodePtr;
			newNodePtr->next = cursor;
		}
		// the previous next pointer will point to newNodePtr
		// the newNodePtr next pointer will point to cursor.
		else
		{
			previous->next = newNodePtr;
			newNodePtr->next = cursor;
		}
	}
}
// Print all function to output document file.
void Print(struct router RT[100][100], int lastRouterID)
{
	ofstream outfile;
	outfile.open("document.txt");
	int j = 0;
	outfile << "Converged @ time: " << convergeTime << endl;
	outfile << "With " << convergedHopCount << " instructions." << endl;

	for (int i = 0; i <= lastRouterID; i++)
	{
		outfile << "----- Router " << i << " -----" << endl;
		outfile << "Destination     Cost     Next Hop" << endl;
		while (RT[j][i].destination != -1)
		{
			outfile << RT[j][i].destination << "\t" << RT[j][i].cost << "\t"
				<< RT[j][i].nextHop << endl;
			j++;
		}
		outfile << "------------------------------" << endl;
	}
	outfile.close();
	 
}
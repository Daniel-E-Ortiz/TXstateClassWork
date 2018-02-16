#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <string.h>
#include <stdlib.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <time.h>
#include <sys/time.h>
#include <unistd.h>

using namespace std;
//struct containing the IP and timestamp of each agent when they joined.
struct ag_l{
	string IP;
	int hour;
	int minute;
	int second;
	int milsecond;
};

/*
int socket(int domain, int type, int protocol);
int bind(int sockFd, const struct sockAddr *my_addr, socklen_t addrlen);
int listen(int SockFd, int backlog);
int accept(int sockFd, struct SockAddr *my_addr, socklen_t *addrlen);
*/
void RemoveElement(vector<ag_l> &,string);
void outLog(string);
int main(int argc,char *argv[])
{
	vector<ag_l> list;
	/* 
	* argv[0] == name of file
	* argv[1] == Server Port
	*/
	string name_of_file = argv[0];
	string agent_IP;
	string output;
	int server_port;
	int sockFd, agentFd, index, bindresult;
	char action[10];
	char response[256];
	struct sockaddr_in server_addr, agent_addr;
	bool onList = false;
	if((sockFd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		printf("ERROR: SOCKET FAILED.\n");
		return 0;
	}
	bzero((char *) &server_addr, sizeof(server_addr));
	server_port = atoi(argv[1]);
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(server_port);

	if ((bindresult = bind(sockFd, (sockaddr *)&server_addr, sizeof(server_addr))) < 0)
	{
		printf("ERROR: BIND FAILED.\n");
		
	}
	printf("Bind: %d\n",bindresult);
	struct timeval tv;
	struct timezone tz;
	struct tm *tm;
	while(1)
	{
		onList = false;
		listen(sockFd,5);
		socklen_t agent_len = sizeof(agent_addr);
		if(agentFd = accept(sockFd,(struct sockaddr *) &agent_addr, &agent_len) < 0)
		{
			printf("ERROR: ACCEPT FAILED.\n");
			return 0;
		}
		agent_IP = inet_ntoa(agent_addr.sin_addr);
		memset(action,0,10);
		read(agentFd,action,10);

		if(strcmp(action,"#JOIN") == 0)
		{
			for(int i = 0; i < list.size(); i++)
			{
				if(!list[i].IP.compare(agent_IP))
				{
					onList = true;
					printf("$ALREADY MEMBER\n");
					sprintf(response,"%s","$ALREADY MEMBER");
					write(agentFd,response,strlen(response));
					output ="Received a \"#JOIN\" action from \"";
					output.append(agent_IP).append("\"");
					outLog(output);
					break;
				}
			}
			if (onList == false)
			{
				printf("$OK\n");
				sprintf(response,"%s","$OK");
				write(agentFd,response,strlen(response));
				output ="Received a \"#JOIN\" action from \"";
				output.append(agent_IP).append("\"");
				outLog(output);
				output = "Responded to agent \"";
				output.append(agent_IP).append("\" with \"$OK\""); 
				outLog(output);
				gettimeofday(&tv,&tz);
				tm = localtime(&tv.tv_sec);
				ag_l newStruct;
				newStruct.IP = agent_IP;
				newStruct.hour = tm->tm_hour;
				newStruct.minute = tm->tm_min;
				newStruct.second = tm->tm_sec;
				newStruct.milsecond = tv.tv_usec/1000;
				list.push_back(newStruct);
			}

		}
		else if(strcmp(action,"#LEAVE") == 0)
		{
			for(int i = 0; i < list.size(); i++)
			{
				if(!list[i].IP.compare(agent_IP))
				{
					onList = true;
					break;
				}
			}
			if (onList)
			{
				printf("$OK.\n");
				sprintf(response,"%s","$OK");
				write(agentFd,response,strlen(response));
				output ="Received a \"#LEAVE\" action from \"";
				output.append(agent_IP).append("\"");
				outLog(output);
				output = "Responded to agent \"";
				output.append(agent_IP).append("\" with \"$OK\""); 
				outLog(output);
				RemoveElement(list,agent_IP);
			}
			else
			{
				printf("$NOT MEMBER.\n");
				sprintf(response,"%s","$NOT MEMBER");
				output ="Received a \"#LEAVE\" action from \"";
				output.append(agent_IP).append("\"");
				outLog(output);
				output = "Responded to agent \"";
				output.append(agent_IP).append("\" with \"$NOT MEMBER\""); 
				outLog(output);
				write(agentFd,response,strlen(response));
			}
		}
		else if(strcmp(action,"#LIST") == 0)
		{	
			for(int i = 0; i < list.size(); i++)
			{
				if(!list[i].IP.compare(agent_IP))
				{
					onList = true;
					break;
				}
			}
			if (onList)
			{
				for(int i = 0; i < list.size(); i++)
				{
					index = i+1;
					gettimeofday(&tv,&tz);
					tm = localtime(&tv.tv_sec);
					int duration = ((tm->tm_hour - list[i].hour)*3600) 
								+ ((tm->tm_min - list[i].minute)*60) 
								+ (tm->tm_sec - list[i].second)
								+ ((tv.tv_usec/1000 - list[i].milsecond)/1000);
					sprintf(response, "Agent %d: %s Duration: %d seconds.", index, list[i].IP.c_str(), duration);
					output ="Received a \"#JOIN\" action from \"";
					output.append(agent_IP).append("\"");
					outLog(output);
					output = "Responded to agent \"";
					output.append(agent_IP).append("\" with \"").append(response).append("\""); 
					outLog(output);
					write(agentFd,response,strlen(response));
				}
			}
			else
			{
				output ="No response is supplied to agent \"";
				output.append(agent_IP).append("\" (agent not active)"); 
				outLog(output);
			}
		}
		else if(strcmp(action,"#LOG") == 0)
		{
				output ="Received a \"#LOG\" action from \"";
				output.append(agent_IP).append("\"");
				outLog(output);
				output = "Responded to agent \"";
				output.append(agent_IP).append("\" with \"log.txt\""); 
				outLog(output);
			string line;
			ifstream logfile;
			logfile.open("log.txt");
			while (!logfile.eof()) 
			{
				getline(logfile,line);
				if(logfile.eof())
					sprintf(response,"%s",line.c_str());
				else
					sprintf(response,"%s\r\n",line.c_str());
				write(agentFd,response,strlen(response)); 
    		}
    		logfile.close();
		}
		else
		{
			printf("ERROR: COMMAND DOES NOT EXIST.\n");
			return 0;
		}
	}
	return 0; 
}

void outLog(string output)
{
   ofstream outfile;
   char now[15];
   struct timeval tv;
   struct timezone tz;
   struct tm *tm;
   
   gettimeofday(&tv,&tz);
   tm=localtime(&tv.tv_sec);
   sprintf(now, "%d:%02d:%02d:%d", tm->tm_hour, tm->tm_min, tm->tm_sec, tv.tv_usec/1000);
   outfile.open("log.txt", std::ios::out | std::ios::app);
   outfile << "\"" << now << "\": " << output << "\r\n";
   outfile.close();
   cout << "\"" << now << "\": " << output << "\r\n";
}

void RemoveElement(std::vector<ag_l> & listing, std::string AgentIP) 
{
   listing.erase(
      std::remove_if(listing.begin(), listing.end(), [&](ag_l const & listing) {
         return listing.IP == AgentIP;
      }),
      listing.end());
}
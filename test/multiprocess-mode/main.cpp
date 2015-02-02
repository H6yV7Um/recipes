// This autogenerated skeleton file illustrates how to build a server.
// You should copy it to another filename to avoid overwriting it.

#include "gen-cpp/Service.h"
#include <thrift/protocol/TBinaryProtocol.h>
#include "TNonblockingServer.h"
//#include <thrift/server/TNonblockingServer.h>
#include <thrift/transport/TServerSocket.h>
#include <thrift/transport/TBufferTransports.h>
#include <concurrency/PosixThreadFactory.h>
#include <thrift/concurrency/Exception.h>

#include <sys/types.h>
#include <unistd.h>
#include <iostream>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/ioctl.h>

using namespace std;

using namespace ::apache::thrift;
using namespace ::apache::thrift::concurrency;
using namespace ::apache::thrift::protocol;
using namespace ::apache::thrift::transport;
using namespace ::apache::thrift::server;



using boost::shared_ptr;

using namespace  ::weibo;



class ServiceHandler : virtual public ServiceIf {
 public:
  ServiceHandler() {
    // Your initialization goes here
  }

  void control(Response& _return, const Request& param) {
    // Your implementation goes here
    printf("control:%d\n",getpid());
    _return.data = param.data;
    return;
  }

};

vector<pid_t> gWorks;
int g_socket = THRIFT_INVALID_SOCKET;
int g_port = 9090;
int numWorks = 2;
int run = false;



int createServer(){
	try
	{
		//shared_ptr<ServiceHandler> handler(new ServiceHandler());
		shared_ptr<ServiceHandler> handler(new ServiceHandler());
		shared_ptr<TProcessor> processor(new ServiceProcessor(handler));
		shared_ptr<TTransportFactory> transportFactory(new TBufferedTransportFactory());
		shared_ptr<TProtocolFactory> protocolFactory(new TBinaryProtocolFactory());

		shared_ptr<ThreadManager> threadManager = ThreadManager::newSimpleThreadManager(8);
		shared_ptr<PosixThreadFactory> threadFactory = shared_ptr<PosixThreadFactory>(new PosixThreadFactory());
		threadManager->threadFactory(threadFactory);
		threadManager->start();

		shared_ptr<TNonblockingServer> server(new TNonblockingServer(processor, protocolFactory,g_port,g_socket,threadManager));	
		//server->serve();
	}catch(TException e){
		cout<<"error:"<<e.what()<<endl;
	}
}


void child_exit(int)
{
	cout<<"child_exitchild_exitchild_exitchild_exit"<<endl;
	exit(0);
}

int processorWork(){
	signal(SIGCHLD, SIG_DFL);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, SIG_IGN);
	signal(SIGTERM, child_exit);
	cout<<"i'm work createserver"<<endl;
	createServer();
	cout<<"exit"<<endl;
	return 0;
}

int initServer(){
        int s = socket(AF_INET,SOCK_STREAM,0);
        if(s == -1){
                return -1;
        }
	g_socket = s;
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(g_port);
        addr.sin_addr.s_addr = inet_addr("0.0.0.0");
        
	//set no block
	int flag = 1; 
    	ioctl(s, FIONBIO, &flag); 

	bind(s,(struct sockaddr*)&addr,sizeof(struct sockaddr_in));
	listen(s,10240);
}

int tryWork(){
	pid_t pid = fork();
	if(pid == -1){
		return 0;
	}
	if(pid == 0){
		int ret = 0;
		
		close(g_socket);
		ret = processorWork();
		cout<<"child exit:"<<ret<<endl;
		exit(ret);
	}
	gWorks.push_back(pid);
}

void checkStatus(){
	vector<pid_t>::iterator it = gWorks.begin();
	for(;it != gWorks.end();){
		pid_t pid = *it;
		printf("child: %d",pid);
		bool isdead = ((kill(pid, 0) != 0 && errno == ESRCH) ||waitpid(pid, NULL, WNOHANG) == pid);
		if(isdead){
			it = gWorks.erase(it);
		}else{
			it++;
		}

	}
	printf("\n");
}

void checkWorks(){
	cout<<"fork.."<<numWorks-gWorks.size()<<endl;
	for(int i=0;i<numWorks-gWorks.size();i++){
		tryWork();
	}
}


void child_exit_info(int)
{
    cout<<"child exit"<<endl;
}

void prog_exit(int){
   cout<<"prog_exit"<<endl;
   run = false;
}


int msleep(unsigned long milisec)
{
    struct timespec req={0};
    time_t sec=(int)(milisec/1000);
    milisec=milisec-(sec*1000);
    req.tv_sec=sec;
    req.tv_nsec=milisec*1000000L;
    while(nanosleep(&req,&req)==-1){
	cout<<"sleep"<<errno<<endl;
	continue;
    }
    return 1;
}


int main(int argc, char **argv) {

	signal(SIGCHLD, child_exit_info);
	signal(SIGPIPE, SIG_IGN);
	signal(SIGINT, prog_exit);
	signal(SIGTERM, prog_exit);	
	
	
	initServer();
	
	//for(int i=0;i<numWorks;i++){
	//	tryWork();
	//}
	run = true;	
	while(run){
		int ret = msleep(1000);
		cout<<"run........"<<ret<<endl;
		checkStatus();
		checkWorks();
	}
	close(g_socket);
	cout<<"hello world"<<endl;
	for(int i=0;i<gWorks.size();i++){
        	kill(gWorks[i],SIGTERM);
	}
	
	while( ::wait(NULL) != -1 || errno != ECHILD ) {
		;
	}

}


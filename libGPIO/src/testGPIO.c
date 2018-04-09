#include <stdio.h> 
#include <string.h>   //strlen 
#include <stdlib.h> 
#include <stdint.h>
#include <errno.h> 
#include <unistd.h>   //close 
#include <arpa/inet.h>    //close 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/in.h> 
#include <string.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros 
#include <stdlib.h>
#include <GPIO.h>


#define TRUE   1 
#define FALSE  0 
#define PORT 22000


int l1,l2,l3,l4,l5;


const char *file_path = "/home/root/image.jpg";
const char *login_path = "/home/root/login.txt";
const char *command = "fswebcam -d /dev/video0 -r 920x720 /home/root/image.jpg ";
size_t fileLen;

static char encoding_table[] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H',
                                'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P',
                                'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
                                'Y', 'Z', 'a', 'b', 'c', 'd', 'e', 'f',
                                'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n',
                                'o', 'p', 'q', 'r', 's', 't', 'u', 'v',
                                'w', 'x', 'y', 'z', '0', '1', '2', '3',
                                '4', '5', '6', '7', '8', '9', '+', '/'};
static char *decoding_table = NULL;
static int mod_table[] = {0, 2, 1};

void build_decoding_table() {

  decoding_table = malloc(256);

  for (int i = 0; i < 64; i++)
    decoding_table[(unsigned char) encoding_table[i]] = i;
}

char *base64_encode(const unsigned char *data,
                    size_t input_length,
                    size_t *output_length) {

  *output_length = 4 * ((input_length + 2) / 3);

  char *encoded_data = malloc(*output_length);
  if (encoded_data == NULL) return NULL;

  for (int i = 0, j = 0; i < input_length;) {

    uint32_t octet_a = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_b = i < input_length ? (unsigned char)data[i++] : 0;
    uint32_t octet_c = i < input_length ? (unsigned char)data[i++] : 0;

    uint32_t triple = (octet_a << 0x10) + (octet_b << 0x08) + octet_c;

    encoded_data[j++] = encoding_table[(triple >> 3 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 2 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 1 * 6) & 0x3F];
    encoded_data[j++] = encoding_table[(triple >> 0 * 6) & 0x3F];
  }

  for (int i = 0; i < mod_table[input_length % 3]; i++)
    encoded_data[*output_length - 1 - i] = '=';

  return encoded_data;
}

char* ReadFile(const char *name)
{
  FILE *file;
  unsigned char *buffer;
  char *lobi;

  //Open file                                                                                                                                                                                                
  file = fopen(name , "rb");
  if (!file)
    {
      fprintf(stderr, "Unable to open file %s", name);
    }

  //Get file length                                                                                                                                                                                          
  fseek(file, 0, SEEK_END);
  fileLen=ftell(file);
  fseek(file, 0, SEEK_SET);

  //Allocate memory                                                                                                                                                                                          
  buffer=(char *)malloc(fileLen+1);
  if (!buffer)
    {
      fprintf(stderr, "Memory error!");
      fclose(file);
      
    }

  //Read file contents into buffer                                                                                                                                                                           
  fread(buffer, fileLen, 1, file);
  size_t output_length = 0; // note *NOT* a pointer
  lobi = base64_encode(buffer, fileLen, &output_length); // note address-of operator
  //printf("Data: %s\n", lobi);
  fclose(file);
  //insert_blob(buffer);
  free(buffer);
  return lobi;
}


void server(){ 

    //Set de pines/////////////////////////////
    

    setup_io();
    configure_pin(4); //garaje
    configure_pin(27); //sala
    configure_pin(17);  //cocina
    configure_pin(3);   //cuarto
    configure_pin(2);   //cuarto
    configure_pin(18);  //Puerta garaje
    configure_pin(25);  //Puerta Principal
    configure_pin(24);  //Puerta Puerta cuarto
    configure_pin(8);   //Puerta cuarto
   




    ////////////////////////////////////////
    l1,l2,l3,l4,l5 = 0;
    int opt = TRUE;  
    int convertdata;
    int master_socket , addrlen , new_socket , client_socket[30] , 
          max_clients = 30 , activity, i , valread , sd;  
    int max_sd;  
    struct sockaddr_in address;  
        
    char buffer[1025];  //data buffer of 1K 
        
    //set of socket descriptors 
    fd_set readfds;  
        
    //a message 
    char *message = "ECHO Daemon v1.0 \r\n";  
    
    //initialise all client_socket[] to 0 so not checked 
    for (i = 0; i < max_clients; i++)  
    {  
        client_socket[i] = 0;  
    }  
        
    //create a master socket 
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)  
    {  
        perror("socket failed");  
        exit(EXIT_FAILURE);  
    }  
    
    //set master socket to allow multiple connections , 
    //this is just a good habit, it will work without this 
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt, 
          sizeof(opt)) < 0 )  
    {  
        perror("setsockopt");  
        exit(EXIT_FAILURE);  
    }  
    
    //type of socket created 
    address.sin_family = AF_INET;  
    address.sin_addr.s_addr = INADDR_ANY;  
    address.sin_port = htons( PORT );  
        
    //bind the socket to localhost port 8888 
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)  
    {  
        perror("bind failed");  
        exit(EXIT_FAILURE);  
    }  
    //printf("Listener on port %d \n", PORT);  
        
    //try to specify maximum of 3 pending connections for the master socket 
    if (listen(master_socket, 3) < 0)  
    {  
        perror("listen");  
        exit(EXIT_FAILURE);  
    }  
        
    //accept the incoming connection 
    addrlen = sizeof(address);  
    //puts("Waiting for connections ...");  
        
    while(TRUE)  
    {  
        //clear the socket set 
        FD_ZERO(&readfds);  
    
        //add master socket to set 
        FD_SET(master_socket, &readfds);  
        max_sd = master_socket;  
            
        //add child sockets to set 
        for ( i = 0 ; i < max_clients ; i++)  
        {  
            //socket descriptor 
            sd = client_socket[i];  
                
            //if valid socket descriptor then add to read list 
            if(sd > 0)  
                FD_SET( sd , &readfds);  
                
            //highest file descriptor number, need it for the select function 
            if(sd > max_sd)  
                max_sd = sd;  
        }  
    
        //wait for an activity on one of the sockets , timeout is NULL , 
        //so wait indefinitely 
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);  
      
        if ((activity < 0) && (errno!=EINTR))  
        {  
            printf("select error");  
        }  
            
        //If something happened on the master socket , 
        //then its an incoming connection 
        if (FD_ISSET(master_socket, &readfds))  
        {  
            if ((new_socket = accept(master_socket, 
                    (struct sockaddr *)&address, (socklen_t*)&addrlen))<0)  
            {  
                perror("accept");  
                exit(EXIT_FAILURE);  
            }  
            
            //inform user of socket number - used in send and receive commands 
            //printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs (address.sin_port));  
          
            //send new connection greeting message 
            if( send(new_socket, message, strlen(message), 0) != strlen(message) )  
            {  
                perror("send");  
            }  
                
            //puts("Welcome message sent successfully");  
                
            //add new socket to array of sockets 
            for (i = 0; i < max_clients; i++)  
            {  
                //if position is empty 
                if( client_socket[i] == 0 )  
                {  
                    client_socket[i] = new_socket;  
                    //printf("Adding to list of sockets as %d\n" , i);  
                        
                    break;  
                }  
            }  
        }  
        //else its some IO operation on some other socket
        for (i = 0; i < max_clients; i++)  
        {  
            sd = client_socket[i];  
                
            if (FD_ISSET( sd , &readfds))  
            {  
                //Check if it was for closing , and also read the 
                //incoming message
                if ((valread = read( sd , buffer, 1024)) == 0)  
                {  
                    //Somebody disconnected , get his details and print 
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addrlen);  
                   // printf("Host disconnected , ip %s , port %d \n" , 
                     //     inet_ntoa(address.sin_addr) , ntohs(address.sin_port));  
                        
                    //Close the socket and mark as 0 in list for reuse 
                    close( sd );  
                    client_socket[i] = 0;  
                }  
                    
                //Echo back the message that came in 
                else
                {  
                    //set the string terminating NULL byte on the end 
                    //of the data read 
                    
                    if(strcmp(buffer, "0\n") == 0){    
                    	int status = system(command);
                        char * msg = ReadFile(file_path);
			printf("%s\n","Image send");
                        send(sd , msg , strlen(msg) , 0 );   
			char * msg1 = "\n";
                        send(sd , msg1 , strlen(msg1) , 0 ); 
                  
                    } 
                    if(strcmp(buffer, "1\n") == 0){
                    	if(l1==1){
				l1=0;
				printf("%s\n","Ligth1 OFF");
				set_pin(4,0);
			} 
			else{
				l1=1;
				printf("%s\n","Ligth1 ON");
				set_pin(4,1);
			}             
                    }
		    if(strcmp(buffer, "2\n") == 0){
                        if(l2==1){
				l2=0;
				printf("%s\n","Ligth2 OFF");
				set_pin(27,0);
			} 
			else{
				l2=1;
				printf("%s\n","Ligth2 ON");
				set_pin(27,1);
			}                     
                    }
		    if(strcmp(buffer, "3\n") == 0){
                        if(l3==1){
				l3=0;
				printf("%s\n","Ligth3 OFF");
				set_pin(17,0);
			} 
			else{
				l3=1;
				printf("%s\n","Ligth3 ON");
				set_pin(17,1);
			}                     
                    }
		    if(strcmp(buffer, "4\n") == 0){
                        if(l4==1){
				l4=0;
				printf("%s\n","Ligth4 OFF");
				set_pin(3,0);
			} 
			else{
				l4=1;
				printf("%s\n","Ligth4 ON");
				set_pin(3,1);
			}                    
                    }
                    if(strcmp(buffer, "5\n") == 0){
                        if(l5==1){
				l5=0;
				printf("%s\n","Ligth5 OFF");
				set_pin(2,0);
			} 
			else{
				l5=1;
				printf("%s\n","Ligth5 ON");
				set_pin(2,1);
			}                     
                    }
		    if(strcmp(buffer, "6\n") == 0){
			printf("%s ","Signals send");
			char  str1[1];
			sprintf(str1, "%d", l1);
			printf("%s",str1);
			char  str2[1];
			sprintf(str2, "%d", l2);
			printf("%s",str2);
			char  str3[1];
			sprintf(str3, "%d", l3);
			printf("%s",str3);
			char  str4[1];
			sprintf(str4, "%d", l4);
			printf("%s",str4);
			char  str5[1];
			sprintf(str5, "%d", l5);
			printf("%s",str5);
			char  str6[1];
			sprintf(str6, "%d", get_pin(18));
			printf("%s",str6);
			char  str7[1];
			sprintf(str7, "%d", get_pin(25));
			printf("%s",str7);
			char  str8[1];
			sprintf(str8, "%d", get_pin(24));
			printf("%s",str8);
			char  str9[1];
			sprintf(str9, "%d", get_pin(8));
			printf("%s\n",str9);
		
                        send(sd , str1 , strlen(str1) , 0 ); 
			send(sd , str2 , strlen(str2) , 0 ); 
			send(sd , str3 , strlen(str3) , 0 ); 
			send(sd , str4 , strlen(str4) , 0 ); 
			send(sd , str5 , strlen(str5) , 0 ); 
			send(sd , str6 , strlen(str6) , 0 ); 
			send(sd , str7 , strlen(str7) , 0 ); 
			send(sd , str8 , strlen(str8) , 0 ); 
			send(sd , str9 , strlen(str9) , 0 ); 



			char * msg = "\n";
                        send(sd , msg , strlen(msg) , 0 );       
			         
                    }
		    if(strcmp(buffer, "7\n") == 0){	
			char buff[1024];
    			FILE *f = fopen(login_path, "r");
    			fgets(buff, 1024, f);
   			fclose(f);
			printf("%s\n","sending login\n");
 		        send(sd , buff , strlen(buff) , 0 );  
		    }
		    
		    
                                       
                }  
            }  
        }  
    }  
}


int main(int argc, char const *argv[])
{
    server();
    return 0;
}
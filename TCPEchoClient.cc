/*
 *   C++ sockets on Unix and Windows
 *   Copyright (C) 2002
 *
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation; either version 2 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program; if not, write to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include "YASL.h"      // For Socket and SocketException
#include <iostream>    // For cerr and cout
#include <cstdlib>     // For atoi()
#include "checkArgs.h"

const uint32_t RCVBUFSIZE = 32;    // Size of receive buffer

int main(int argc, char *argv[]) {

  checkArgs* datos = new checkArgs(argc,argv);
  std::string servAddress;
  uint16_t echoServPort;
  std::string echoString;
  uint32_t echoStringLen;
  std::string nombreArchivo;

serverAddress = datos->getArgs().SERVER;
echoServPort = datos->getArgs().PORT;
nombreArchivo = datos->getArgs().ARCHIVO;
  
  echoString = "GET / HTTP/1.1\r\nHost: " + servAddress; 
  echoStringLen = echoString.length();  
  
  try {
    // Establish connection with the echo server
	TCPSocket sock(servAddress, echoServPort);

  std::ofstream archivo;
  archivo.open(nombreArchivo);
	 
  
    // Send the string to the echo server
    sock.send(echoString.c_str(), echoStringLen);
  
    char echoBuffer[RCVBUFSIZE + 1];    // Buffer for echo string + \0
    uint32_t bytesReceived = 0;              // Bytes read on each recv()
    uint32_t totalBytesReceived = 0;         // Total bytes read
    
	// Receive the same string back from the server
    std::cout << "Received: ";               // Setup to print the echoed string
    while (totalBytesReceived < echoStringLen) {
      // Receive up to the buffer size bytes from the sender
      if ((bytesReceived = (sock.recv(echoBuffer, RCVBUFSIZE))) <= 0) {
        std::cerr << "Unable to read";
        archivo.close();
        exit(EXIT_FAILURE);
      }
      totalBytesReceived += bytesReceived;     // Keep tally of total bytes
      echoBuffer[bytesReceived] = '\0';        // Terminate the string!
      std::cout << echoBuffer;                      // Print the echo buffer
    }
    std::cout << std::endl;

    // Destructor closes the socket
archivo.close();
std::cout<<"Se ha guardado el archivo: "<<nombreArchivo<<std::endl;
   exit(EXIT_FAILURE);

  } catch(SocketException &e) {
    std::cerr << e.what() << std::endl;
    exit(EXIT_FAILURE);
  }


  return EXIT_SUCCESS;
}

# TerminalChat

### User Manual

1. Compile each program separately, for example:
   ```
   g++ server.cpp -o server
   g++ client.cpp -o client
   ```

2. Open two terminal windows.
   
3. In one terminal, start the server:
   ```
   ./server
   ```

4. In the other terminal, start the client:
   ```
   ./client
   ```

### Explanation

- **Server Side**:
  - Creates a socket, binds to `127.0.0.1:5001`, listens for a connection, and accepts a client.
  - Continuously receives messages from the client, displays them, and prompts the server user to reply.
  
- **Client Side**:
  - Connects to the server at `127.0.0.1:5001`.
  - Allows the client user to send messages to the server and receive responses.

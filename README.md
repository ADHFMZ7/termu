# termu

A simple unix style terminal emulator.

The goal of this project is to run vim relatively well.



## Documentation

The terminal emulator consists of two parts; the terminal front end, and the 
back end.

### Frontend

The front end is the part that is visible to the user. It will be responsible
for rendering the text and performing the actions requested by the backend.

### Backend

The backend will be responsible with interpreting the input stream and parsing
the ANSI escape codes. It will then call the proper functions on the front end.


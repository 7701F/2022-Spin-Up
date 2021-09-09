#ifndef OPFUNC_H_
#define OPFUNC_H_

// Declare drive system variables.
bool pbrake = false;

// Declare driver functions
void tankDrive();
void arcadeDrive();
void customBrake(bool pbrake);
void prosBrake(bool pbrake);

#endif

/*   SDLMain.m - main entry point for our Cocoa-ized SDL app
       Initial Version: Darrell Walisser <dwaliss1@purdue.edu>
       Non-NIB-Code & other changes: Max Horn <max@quendi.de>

    Feel free to customize this file to suit your needs
*/

#import <Cocoa/Cocoa.h>
#include "adonthell.h"

@interface SDLMain : NSObject 
{
    const adonthell::app *Application;
}
    
- (void)init:(const adonthell::app *)theApp;
@end

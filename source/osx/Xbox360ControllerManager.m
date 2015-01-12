//
//  Xbox360ControllerManager.m
//  Xbox360ControllerManager
//
//  Created by Derek van Vliet on 11-05-12.
//  Copyright 2011 Get Set Games. All rights reserved.
//
//  Updated by Halfbot.com 2013-05-14 Ha
//  Added support for 3d-Party Xbox Controllers as well

#import "Xbox360ControllerManager.h"
#include <mach/mach.h>
#include <IOKit/usb/IOUSBLib.h>

// Handle callback for when our device is connected or disconnected. Both events are
// actually handled identically.
static void callbackHandleDevice(void *param,io_iterator_t iterator) {
    io_service_t object=0;
    BOOL update;
        update=FALSE;
    while((object=IOIteratorNext(iterator))!=0) {
        IOObjectRelease(object);
        update=TRUE;
    }
    if(update) [(Xbox360ControllerManager*)param updateControllers];
    

}

@implementation Xbox360ControllerManager

static Xbox360ControllerManager *sharedXbox360ControllerManager = nil;

+(Xbox360ControllerManager *) sharedInstance {
	return sharedXbox360ControllerManager;
}

+(void)initialize {
	if ( self == [Xbox360ControllerManager class] ) {
		if (!sharedXbox360ControllerManager) {
			sharedXbox360ControllerManager = [Xbox360ControllerManager new];
		}
	}
}

-(id)init {
	self = [super init];
	
	if (self) {
        
        controllers = [[NSMutableArray alloc] init];
        
        io_object_t object;
		
        // Get master port, for accessing I/O Kit
        IOMasterPort(MACH_PORT_NULL,&masterPort);
        // Set up notification of USB device addition/removal
        notifyPort=IONotificationPortCreate(masterPort);
        notifySource=IONotificationPortGetRunLoopSource(notifyPort);
        CFRunLoopAddSource(CFRunLoopGetCurrent(),notifySource,kCFRunLoopCommonModes);
		
        // Activate callbacks
        // Wired
        IOServiceAddMatchingNotification(notifyPort, kIOFirstMatchNotification, IOServiceMatching(kIOUSBDeviceClassName), callbackHandleDevice, self, &onIteratorWired);
        callbackHandleDevice(self, onIteratorWired);
        IOServiceAddMatchingNotification(notifyPort, kIOTerminatedNotification, IOServiceMatching(kIOUSBDeviceClassName), callbackHandleDevice, self, &offIteratorWired);
        while((object = IOIteratorNext(offIteratorWired)) != 0)
            IOObjectRelease(object);
        // Wireless
        IOServiceAddMatchingNotification(notifyPort, kIOFirstMatchNotification, IOServiceMatching("WirelessHIDDevice"), callbackHandleDevice, self, &onIteratorWireless);
        callbackHandleDevice(self, onIteratorWireless);
        IOServiceAddMatchingNotification(notifyPort, kIOTerminatedNotification, IOServiceMatching("WirelessHIDDevice"), callbackHandleDevice, self, &offIteratorWireless);
        while((object = IOIteratorNext(offIteratorWireless)) != 0)
            IOObjectRelease(object);
        
       // CFRunLoopRun();
        //[[NSRunLoop currentRunLoop] run];
        

    }
	
	return self;
}

-(void)dealloc {
	[controllers release];
	
	[super dealloc];
}

-(Xbox360Controller*)controllerWithHid:(io_object_t)hid {
    for (Xbox360Controller* controller in controllers) {
        if (controller.myHid == hid) {
            return controller;
        }
    }
    
    return nil;
}

-(int)controllerCount {
    return (int)controllers.count;
}

-(Xbox360Controller*)getController:(int)index
{
    if ( controllers != NULL && index < [controllers count] )
        return [controllers objectAtIndex:index];
    else
        return NULL;
}

// Make sure a name is as nice as possible for eventually going into the XML for the driver
static NSString* SanitiseName(NSString *name)
{
    NSMutableString *output;
    int i;
    
    output = [NSMutableString stringWithCapacity:100];
    for (i = 0; i < [name length]; i++)
    {
        unichar c = [name characterAtIndex:i];
        if (c == ' ')
            c = '_';
        else if (!(((c >= 'a') && (c <= 'z')) || ((c >= 'A') && (c <= 'Z')) || ((c >= '0') && (c <= '9')) || (c == '_')))
            continue;
        [output appendFormat:@"%C", c];
    }
    return output;
}

// Get some sort of CF type for a field in the IORegistry
static id GetDeviceValue(io_service_t device, NSString *key)
{
    CFTypeRef value;
    
    value = IORegistryEntrySearchCFProperty(device, kIOServicePlane, (CFStringRef)key, kCFAllocatorDefault, kIORegistryIterateRecursively);
    return [((NSObject*)value) autorelease];
}

// Update the device list from the I/O Kit
-(void)updateControllers {
    CFMutableDictionaryRef hidDictionary;
    IOReturn ioReturn;
    io_iterator_t iterator;
    io_object_t hidDevice;
        
	NSMutableArray *newControllers = [[NSMutableArray alloc] init];
	
    // Add new items
    hidDictionary=IOServiceMatching(kIOHIDDeviceKey);
	
    ioReturn=IOServiceGetMatchingServices(masterPort,hidDictionary,&iterator);
    if((ioReturn!=kIOReturnSuccess)||(iterator==0)) {
		[newControllers release];
        return;
    }

    while((hidDevice=IOIteratorNext(iterator))) {
        BOOL deviceWired = IOObjectConformsTo(hidDevice, "ControllerClass");
        
        // Added to support third party XboxControllers, Tested on AfterGlow
        //(http://www.amazon.com/Afterglow-AX-1-Controller-Xbox-360-Green/dp/B003IU01TY)
        BOOL deviceWired2 = IOObjectConformsTo(hidDevice, "Xbox360ControllerClass");
        BOOL deviceWireless = IOObjectConformsTo(hidDevice, "WirelessHIDDevice");
        
        
        NSNumber *vendorValue, *productValue;
        UInt16 vendor,product;
        
        vendorValue = GetDeviceValue(hidDevice, @"idVendor");
        vendor = [vendorValue intValue];
        
        productValue = GetDeviceValue(hidDevice, @"idProduct");
        product = [productValue intValue];

        io_name_t className;
        IOReturn ioReturnValue = kIOReturnSuccess;
		ioReturnValue = IOObjectGetClass(hidDevice, className);
		
        // Print Class for debugging
        //NSLog("%s\n",className);
        
        //Dump Venter Info
        if ((vendorValue != nil) && (productValue != nil))
        {
            NSNumber *key;
            
            key = [NSNumber numberWithUnsignedInt:(vendor << 16) | product];
            NSString *name = GetDeviceValue(hidDevice, @"USB Product Name");
            if (name == nil)
                name = [NSString stringWithFormat:@"Unknown_%.4x_%.4x", vendor, hidDevice];
            else
                name = SanitiseName(name);
        }

        if ((!deviceWired) && (!deviceWired2) && (!deviceWireless) )
        {
            IOObjectRelease(hidDevice);
            continue;
        }
		
		Xbox360Controller *controller = [self controllerWithHid:hidDevice];
		if (controller) {
			if (controller.deviceIsAccessible) {
				[newControllers addObject:controller];
			}
		}
		else {
			controller = [[Xbox360Controller alloc] initWithHidDevice:hidDevice];
			if (controller) {
				[newControllers addObject:controller];
				[controller release];
			}
		}
		
    }
    IOObjectRelease(iterator);
    
    for (Xbox360Controller *controller in controllers) {
        if ([newControllers indexOfObject:controller] == NSNotFound) {
            [controller disconnect];
        }
    }
	[controllers release];
	controllers = newControllers;
	[[NSNotificationCenter defaultCenter] postNotificationName:XBOX360CONTROLLERS_UPDATED object:nil];
}

-(void)setAllDelegates:(id<Xbox360ControllerDelegate>)d {
    for (Xbox360Controller* c in controllers) {
        c.delegate = d;
    }
}
@end

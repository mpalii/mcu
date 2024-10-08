# ECE4760 - Spring 2012  
[ECE4760 playlist](https://www.youtube.com/playlist?list=PLXtbXftdltFMcr5rtiWoaTsBULA_gKXNl)  

### 1 - Course introduction
[ECE4760](http://people.ece.cornell.edu/land/courses/ece4760/)  
[Old AVR-based home page](http://people.ece.cornell.edu/land/courses/ece4760/index_2015_atmega1284.html)  
[Old Homework](http://people.ece.cornell.edu/land/courses/ece4760/homework/oldhomework.html) 

Laboratory work 1 - reaction time tester  
Laboratory work 2 - digital multimeter: voltage, frequency and resistance (DMM)  
Laboratory work 3 - Markov process sequencer (probabilistic sequencer followed by an FM synthesizer)  
Laboratory work 4 - PID motor controler (small real-time kernel)  

Final project constraints:  
- 75 US dollars budget  
- no weapon control system  
- AVR architecture (mega644 lot of IO, tiny13 small size SOT23 3mmx3mm)  

Course requirements:  
- C knowledge (C Programming Language - Brian W. Kernighan, Dennis M. Ritchie)  
- Basics of electronics (Practical Electronics for Inventors - Paul Scherz, Simon Monk)   

Every microcontroller has about the same facilities as every other microcontroller but every single detail is different. 
Microcontroller is a processor plus peripherals and typically also program memory and RAM so that it's a complete one chip solution as a standalone computer. 

The way we're going to be using microcontrollers is rather low level controllers where you will have access to and control the voltage on up to 32 IO lines 
so your program will have direct control of the logic state of 32 logic lines you'll be able to read an analog voltage off of eight input lines. 
This processor has three hardware timers, eight ADD channels, serial communication etc. 

Microcontroller is a self-contained system.   

It is important to optimize hardware vs software. If it comes down to writing a thousand lines of C or using one TTL package which would you rather do? 
Look for elegant solutions. You're gonna have to worry not only about logic levels and abstract symbol processing you're gonna have to worry about noise, 
filtering, Thevenin equivalent impedance of I/O ports.   

Algorithms we're going to use are mostly simple state machines. Most of the labs will come down to building a state machine. 
And the complexity occurs in a couple of different ways. One is that all the programming is going to be real-time and so you 
will have millisecond deadlines everywhere that you have to meet, so your code has to be simple and compact, and you have to 
think through the worst case timing. Secondly there's always in every program you write in this class there's going to be at 
least one interrupts running. There's going to be the main line code plus one interrupts running which means you have a concurrent 
system you have two threads of control. They're running simultaneously or alternating running and you have to worry seriously 
about concurrent issues particularly data integrity of multibyte objects. But most of the of the complexity of the course comes 
in understanding the control system for the peripherals and how that control system interacts with external circuitry.  

Everything you do in this lab is going to have a software component and an external hardware component which have to link up 
through the I/O structure so that's where the interesting part of this class occurs.  

[Homework 1 - Due at the beginning of lab 1](https://people.ece.cornell.edu/land/courses/ece4760/homework/s2012/hw1.html)  

### 2 - MCU and lab 1  
[Lab 1](https://people.ece.cornell.edu/land/courses/ece4760/labs/s2012/lab1.html)  

QUESTIONS:  
(1<<OCIE0A) - 'OCIE0A' is a constant in avr/io.h equals to 1, overall this means take 1 and shift it 1 times to the left. 
In other words it sets bit 1. Interesting way of naming bit one.     

GCC - is an ANSI standard C. There's specific hardware libraries that are available, I/O libraries that are available for this 
architecture, for instance, standard I/O is available so there's a print and a scan, scanf command as there is in almost all variants 
in C. And even though there's no unix running there's no operating system running the C compiler simulates enough of the I/O 
system so that you can print stuff to a terminal, you can receive information from a standard terminal like Hyper Terminal or Putty. 
There is a library to run the liquid crystal display put string put, car so on. There are some very skeletal interrupt service 
routine features that we'll have to fill in by hand. Even though this is an 8-bit microcontroller with no floating-point unit 
there is a floating point library for it, in fact there's two or three, and the speed of the floating point depends on which library 
you happen to link and the default library is not the fastest but that's okay because you'll barely use floating point in this 
course anyway, almost everything will be fixed point for speed. It takes about a hundred and fifty to four hundred cycles to do a 
floating-point multiply. 

6-22
Microcontroller we're going to use is a Atmel mega 644. And you ask why 8-bit? Well, it's cheap and therefore, I can afford to buy 
enough of them that you can afford to blow them up, that's also why we use pdip package because when they've become toast you 
can pop them out and put a new one in, whereas if it's surface mount you're stuck. We blow 40 CPUs a semester something like that. 
That's just what happens, you short an output you're short an output port to ground it's gone, it's really easy to do. Another reason 
that we use 8-bit microcontrollers is probably the majority of CPUs sold in the world are still 8 bits. About 4 or 5 billion a year. 
Another reason is that the clock speeds on these 8-bit machines are fairly low about 16 to 20 megahertz, which means you can 
still like use wires to hook them up to stuff, you can use 18-inch wire and still be reasonably sure that you're going to get a 
result back within one clock cycle. So it's a it's a nice speed for interfacing. There's 32 i/o lines there's four i/o ports - 
that's enough to do a lot of stuff. There's some nice battery saving modes there's some nice power down modes on these little 
processors so that if you're building something that needs a long battery life piece of instrumentation that's going to live on 
your body or something of the sort then it's fairly easy to get the power supply use minimized. And it's really easy to make 
these things go standalone. They have internal oscillators if you turn on the internal oscillator you can take the CPU you put a 3 
volt battery across ground VCC and it'll boot and run. It's all it takes everything's inside it's completely self-contained it 
makes it really easy to build a standalone target system or if you want to use 16 of them to make a crossbar switch or some crazy 
thing then you can do that too fairly easily. And they can be programmed by about 10,000 times which makes them awesome for a 
teaching lab. However they will get used up this semester they're each some of these will be programmed more than 10,000 times and 
they'll stop taking a program and when that happens you're going to have to have the TA help you figure out what's wrong and get 
a new CPU I would prefer you not to change CPUs on the prototype board yourself for the first couple of labs because experience 
shows that almost nobody knows how to unplug a 40 pin pdip without bending the pins and I would like to show you how to do that 
before you bust up a bunch of them. So there's 32 i/o lines - 32 digital i/o, there is no analog i/o on this chip however there are 
six PWM channels pulse width modulation channels a pulse width modulation channel fed through a low-pass filter is an analog output so 
the six PDR PWM channels there's three Hardware timers. You can never do accurate timing in software. You have to do it in hardware. 
Software is just too hard to balance, it's too hard to cycle balance it makes it unmaintainable and unreliable so we'll be always every
single lab every program you write in this class will use at least one of the hardware timers. There's ADC converter: eight channel, 
it's fairly slow you can get ten bits at 10 kilohertz but you can degrade this gracefully if you only need five bits of resolution 
you could run it at least thirty kilohertz, so you can trade off bits of resolution for conversion speed over a fairly large range. 
There's a UART. There's a device that allows a serial control stream. It's called a universal asynchronous receive transmit. 
It's a serializer/deserializer. There's an interrupt on every i/o line which you can set up there's an interrupt. Several interrupts 
on each timer it's about 35 interrupt sources. There's a SPI this serial peripheral interface which is a high-speed serial synchronous 
communication standard as opposed to asynchronous so there's a clock that's associated with this. There's a watchdog timer. This is a 
device if all else fails if your system hangs the watchdog timer will reset it and get the code running again. And this would be important 
in some context let's say that you have a microcontroller which is controlling a radiation gate on a therapeutic machine and that pulls 
the gate open and then crashes and so you got this x-ray beam hitting the patient it'd be really nice if the system resets and turns off 
the beam so a watchdog timer could be considered a safety device or a fail-safe device of various sorts. There's a gigantic 4k of RAM. 
That's data data storage. There's 64 K of programstorage which is flash memory. There's 2K of EEPROM. And just to make things annoying 
accessing each one of those requires a different pointer structure and therefore the read/write commands for each one of these are different. 
Each peripheral, each timer, each i/o line so on has some control registers as usual. 
Timer zero has six control registers:  
TCNT0 - counter itself
TCCR0A  
TCCR0B  
OCR0A
OCR0B
TIMSK0
14:54
TCC are 0 b t CN t 0 OC r 0 a OC r 0 b
15:07
and t IM s k 0 t count zero is actually
15:15
the counter which maintains the tick which maintains the count of how many clock cycles have passed these are
15:22
control registers for setting up various combinations because what you have here is really a timer toolkit
15:28
it not only times intervals you can set up the timer to toggle an IO line
15:34
periodically therefore you can make a square wave without any software you can
15:40
also set it up so that when the count matches the compare register the count
15:48
automatically is reset to zero TI m sk 0
15:53
the time mask sets which of these various events overflow matching these
15:59
two registers and so on triggers and interrupt anything can be interrupted
16:05
and we'll talk about this in horrible detail
16:13
so now starting to talk specifically about lab one for next week first lab is
16:19
next Wednesday it's going to be a course
16:27
introduction to the compiler and the protoboard i/o registers but it'll also
16:33
be the first half of building the the
16:41
reaction time timer which will be finished in the second part that will be the next lab and will basically be using
16:51
two pieces of the microcontroller there'll be an i/o ports and timer zero
17:01
there's four i/o ports amusingly labeled a b c and d and you can look up the
17:08
special functions of each one of them but they all act like general i/o ports
17:17
you can set any bit of any port to be an input or an output within one cycle so
17:26
there is a data Direction register for X where X takes on the value a B C or D so
17:41
there's a data Direction register which takes an 8-bit value and sets the i/o
17:47
direction for each pin a 1 being an output then there is a register called
17:55
an i/o register called port X which when you write to it sets the port
18:05
if the data Direction register is set to a 1 there is a pin X so this output is
18:20
the port X and this is pin x dot y the
18:31
pin register contains the inputs if you set the data Direction register to an
18:39
output and set the port register and
18:44
then read the pin register what do you get the value you just set in the port
18:51
register so these three registers
18:59
control the i/o each i/o pin independently as a logic level for lab 1
19:13
if we go through this I want to talk a little bit about interrupts and then we'll start in with some actual C code
19:20
which by the way you may want to look at before we go through it in class it is the there are three examples in lab 1
19:27
we'll go through them all in the next week or so
19:43
we're going to be running for the first labs we're going to be running the processor at 16 megahertz oh and by the
19:52
way at the end of the semester people tend to swap out crystals for any random
19:58
value they think is going to be useful for their for their final project so some of the CPUs might have 7.14
20:05
megahertz crystals some might have 14.2 some might have 22 they're overclocking
20:13
and so you're going to need to check the crystal on your board everyday to make
20:23
sure it's a 16 megahertz crystal it's a

#### Notes  

check:  
	avrdude -c usbasp -p atmega328p -v  

erease:  
	avrdude -c usbasp -p atmega328p -e  

upload:  
	avrdude -c usbasp -p atmega328p -v -U flash:w:./target/$(PROJECT).hex:i  

fuse-no-divider:  
	avrdude -c usbasp -p atmega328p -U lfuse:w:0xe2:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m  

fuse-no-divider-ext-clk:  
	avrdude -c usbasp -p atmega328p -U lfuse:w:0xff:m -U hfuse:w:0xd9:m -U efuse:w:0xff:m  

TA - teacher assistant   

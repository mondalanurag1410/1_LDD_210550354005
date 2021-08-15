
/*heder file to provide declaration of the ioctl macros*/
#define magic_num 'G' // magic number available for my program, find in Documentation of linux

#define OPERATION _IOW(magic_num, 44,int) // operation macro providing the sequence number
					  //as G magic number have alredy use the sepuence numbers
					  // 00 to 3F and privious program I have used 40 to 43

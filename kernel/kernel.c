void kmain()
{
	char *video_memory = (char *)0xB80000;
	video_memory[0] = '4';
	video_memory[1] = 0x1f;
	video_memory[2] = '2';
	video_memory[3] = 0x1f;
}

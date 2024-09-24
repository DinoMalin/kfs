void kmain()
{
    unsigned char *video_memory = (unsigned char *)0xB8000;

    video_memory[0] = '4';
    video_memory[1] = 0xF1;
    video_memory[2] = '2';
    video_memory[3] = 0xF1;
    video_memory[4] = 'D';
    video_memory[5] = 0x1F;
    video_memory[6] = 'I';
    video_memory[7] = 0x1F;
    video_memory[8] = 'N';
    video_memory[9] = 0x1F;
    video_memory[10] = 'O';
    video_memory[11] = 0x1F;
}

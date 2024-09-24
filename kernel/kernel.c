void kmain()
{
    *((unsigned char *) 0xB8000) = '4';
    *((unsigned char *) 0xB8001) = 0x1F;
    *((unsigned char *) 0xB8002) = '2';
    *((unsigned char *) 0xB8003) = 0x1F;
}

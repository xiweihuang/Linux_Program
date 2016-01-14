int GetInput(const char* info);
void drawDiamond(int radius);

int main()
{
	int r = GetInput("please input radius");
	drawDiamond(r);
	return 0;
}

#include "graphics_utils.h"

IMAGE img;

//初始化窗口
void LoadBgk() {
    loadimage(&img, _T("res//bk.jpg"));
    putimage(0, 0, &img);
    setbkmode(TRANSPARENT);
    settextcolor(BLACK);
}

//设置字体
void SetHeightText(int height) {
    LOGFONT font;
    gettextstyle(&font);
    font.lfHeight = height;
    font.lfWeight = FW_MEDIUM;
    _tcscpy_s(font.lfFaceName, _T("黑体"));
    font.lfQuality = ANTIALIASED_QUALITY;
    settextstyle(&font);
}

//绘制按钮
void DrawButton(int x, int y, int width, int height, const wchar_t* text, int fontsize) {
    setfillcolor(RGB(173, 216, 230));
    solidrectangle(x, y, x + width, y + height);
    SetHeightText(fontsize);
    RECT r = { x, y, x + width, y + height };
    drawtext(text, &r, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
}

//绘制表格
void DrawTable(int x, int y, int width, int height, int rows, int cols) {
	setlinecolor(BLACK);
	for (int i = 0; i <= rows; i++) {
		line(x, y + i * height / rows, x + width, y + i * height / rows);
	}
	for (int j = 0; j <= cols; j++) {
		line(x + j * width / cols, y, x + j * width / cols, y + height);
	}
}

//判断鼠标是否在矩形内
bool IsMouseInRect(int x, int y, int width, int height) {
    MOUSEMSG msg = GetMouseMsg();
    return msg.x >= x && msg.x <= x + width && msg.y >= y && msg.y <= y + height;
}

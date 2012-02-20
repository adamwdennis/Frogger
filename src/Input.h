#ifndef _INPUT_H_
#define _INPUT_H_

#include <windows.h>

class Input
{
public:
	static Input* GetInstance();
	~Input();

	void KeyUpMap(unsigned char key, int x, int y);
	void KeyMap(unsigned char key, int x, int y);
	void HandleInput();

	bool IsDisplayHelp() const { return displayHelp; }
	bool IsDisplayDebugInfo() const { return displayDebugInfo; }
protected:
	Input();

private:
	static Input* p_pInstance;
	bool keyDown[256];
	bool displayDebugInfo;
	bool displayHelp;
};

#endif
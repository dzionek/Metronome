#include <iostream>
#include <cmath>
#include <thread>
#include <atomic>
#include <string>

void metronome(float);

class WaitForEnter
{
public:
	WaitForEnter() : finish(false)
	{
		thr = std::thread([this]() {
			std::string in;
			std::getline(std::cin, in);
			finish = true;
			});
	}
	~WaitForEnter()
	{
		thr.join();
	}
	bool isFinished() const { return finish; }
private:
	std::atomic<bool> finish;
	std::thread thr;
};

int main() {
	float f;
start:
	std::cout << "Hello my lovely musician! I'm your metronome and I would like to help you to feel the rhythm.\nMy options:\n1)Tell me how much BMP I shall play\n2)What is a metronome? Instruction\n3)Who did create me?\n4)Exit\nPick an integer from 1 to 4 and press enter to go to your option.\n";
incorrectnumber:
	std::cin >> f;
	if (std::cin.fail() || floor(f) != f) {
		std::cout << "Emm... Don't try to test me. You wrote something that is not an integer or your integer is very big.\n";
		std::cin.clear();
		std::cin.ignore();
		goto incorrectnumber;
	}
	int i = f;
	switch (i) {
	case 1: std::system("cls");
		std::cout << "You chose the number 1 so please gimme the number of BMP I need to play\n";
		float bmp;
	incorrectnumberbmp:
		std::cin >> bmp;
		if (std::cin.fail() || floor(bmp) != bmp) {
			std::cout << "Emm... Don't try to test me. You wrote something that is not an integer or your integer is not in range.\nPick the number again.\n";
			std::cin.clear();
			std::cin.ignore();
			goto incorrectnumberbmp;
		}
		metronome(bmp);
		std::system("cls");
		goto start;

	case 2: std::system("cls");
		std::cout << "You chose the number 2 and want to know what is a metronome.\nAccording to Wikipedia, a metronome is a device that produces an audible click or other sound at a regular interval that can be set by the user, typically in beats per minute (BPM).\nIn option 1) you need to tell me how many beats per minute you want me to play. Then I will generate system sounds.\nPress Enter to back to the menu\n";
		std::cin.get();
		std::cin.get();
		std::system("cls");
		goto start;

	case 3: std::system("cls");
		std::cout << "You chose the number 3 and want to know who created me.\nI was made by Bartosz Dzionek.\nMeet him on GitHub: github.com/vburtoch.\nFind him on LinkedIn: bit.ly/bd-linkedin.\nPress Enter to back to the menu\n";
		std::cin.get();
		std::cin.get();
		std::system("cls");
		goto start;

	case 4: std::system("cls");
		std::cout << "You chose the number 4 and want to exit.\nBye bye! I'm glad I served you.\n";
		std::this_thread::sleep_for(std::chrono::seconds(3));
		break;

	default: std::cout << "I'm really sorry but I have only option 1, 2, 3 and 4. No more no less. Pick the number again.\n";
		goto incorrectnumber;
	}
	return 0;
}

void metronome(float bmp) {
	std::cout << "I play " << bmp << " BMP.\nPress enter and I will stop";
	std::cin.ignore();
	unsigned nanobmp = floor(6.0 * 10000000000 / bmp);
	WaitForEnter wait;
	while (!wait.isFinished())
	{
		std::cout << "\a";
		std::this_thread::sleep_for(std::chrono::nanoseconds(nanobmp));
	}
	std::cout << "\nOK, that was enough.\nPress enter to back to menu.\n";
	std::cin.get();
}
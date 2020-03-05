#include "CommandInterpreter.h"

int main() {
	CommandInterpreter* shell = new CommandInterpreter();
	shell->Start();
	delete(shell);
	return 0;
}
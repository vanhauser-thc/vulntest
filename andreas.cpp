#include <iostream>
#include <string>

struct WebRequestForm {
  std::string username;
  std::string password;
  double amount_of_money;
};
bool IsValidString(const std::string &string) { return !string.empty(); }
bool IsMoneyInRange(double amount_of_money) { return amount_of_money > 0.0; }
bool LoginUser(const std::string &username, const std::string &password) { return true; }
void LogoutUser(const std::string &username) {}
void ReponseToClient(const std::string &string) { std::cout << "Response to client:  " << string << std::endl; }
void LoggingReponseToClient(const std::string &string) { std::cout << "Logging to client:  " << string << std::endl; }
void WebRequest(const WebRequestForm &request) {
  static std::string username = "";
  static std::string password = "";
  static double amount_of_money = 0.0;
  bool is_input_valid = IsValidString(request.username) && IsValidString(request.password) && IsMoneyInRange(request.amount_of_money);
  if (is_input_valid) {
    username = request.username;
    password = request.password;
    amount_of_money = request.amount_of_money;
  } else
    ReponseToClient("You must provide a valid username and a valid password and a valid "
                    "amount as input!");
  if (is_input_valid && LoginUser(username, password)) {
    // here we do stuff ...
    LogoutUser(username);
    ReponseToClient("Successfully did weird stuff with the money");
  }
  LoggingReponseToClient("Called the service with username = " + username + " and password = " + password);
}
int main(int argc, char *argv[]) {
  std::cout << "admin user does something" << std::endl;
  WebRequestForm admin_request = {"admin", "TopSecret", 5000.0};
  WebRequest(admin_request);
  std::cout << "\n\n--- some time is passing ---\n\n" << std::endl;
  std::cout << "attacker does something" << std::endl;
  double d = strtod(argv[3], NULL);
  std::string arg1(argv[1]);
  std::string arg2(argv[2]);
  WebRequestForm attacker_request = {arg1, arg2, d};
  WebRequest(attacker_request);
  return 0;
}

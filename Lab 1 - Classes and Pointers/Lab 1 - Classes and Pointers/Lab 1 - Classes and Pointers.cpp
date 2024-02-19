#include <iostream>
#include <vector>
#include <string>
#include <memory>

class Achievement {
public:
    Achievement(const std::string& title, const std::string& description, int scoreValue)
        : title_(title), description_(description), scoreValue_(scoreValue) {}

    const std::string& GetTitle() const { return title_; }
    const std::string& GetDescription() const { return description_; }
    int GetScoreValue() const { return scoreValue_; }

private:
    std::string title_;
    std::string description_;
    int scoreValue_;
};

class Game {
public:
    Game(const std::string& name, const std::string& publisher, const std::string& developer)
        : name_(name), publisher_(publisher), developer_(developer) {}

    void AddAchievement(std::shared_ptr<Achievement> achievement) { achievements_.push_back(achievement); }
    const std::vector<std::shared_ptr<Achievement>>& GetAchievements() const { return achievements_; }
    const std::string& GetName() const { return name_; }
    

private:
    std::string name_;
    std::string publisher_;
    std::string developer_;
    std::vector<std::shared_ptr<Achievement>> achievements_;
};

class Platform {
public:
    Platform(const std::string& name, const std::string& manufacturer)
        : name_(name), manufacturer_(manufacturer) {}

    void AddGame(std::shared_ptr<Game> game) { games_.push_back(game); }
    const std::vector<std::shared_ptr<Game>>& GetGames() const { return games_; }
    const std::string& GetName() const { return name_; }
    

private:
    std::string name_;
    std::string manufacturer_;
    std::vector<std::shared_ptr<Game>> games_;
};

void DisplayMenu() {
    std::cout << "1. Create new platform" << std::endl;
    std::cout << "2. Create new game" << std::endl;
    std::cout << "3. Create new achievement" << std::endl;
    std::cout << "4. Display platforms and games" << std::endl;
    std::cout << "5. Exit" << std::endl;
}

int main() {
    std::vector<std::shared_ptr<Platform>> platforms;
    int choice;

    while (true) {
        DisplayMenu();
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        switch (choice) {
        case 1: {
            std::string name, manufacturer;
            std::cout << "Enter platform name: ";
            std::cin >> name;
            std::cout << "Enter platform manufacturer: ";
            std::cin >> manufacturer;
            platforms.push_back(std::make_shared<Platform>(name, manufacturer));
            break;
        }
        case 2: {
            if (platforms.empty()) {
                std::cout << "No platforms available. Please create a platform first.\n";
                break;
            }
            std::string name, publisher, developer;
            std::cout << "Enter game name: ";
            std::cin >> name;
            std::cout << "Enter game publisher: ";
            std::cin >> publisher;
            std::cout << "Enter game developer: ";
            std::cin >> developer;
            platforms.back()->AddGame(std::make_shared<Game>(name, publisher, developer));
            break;
        }
        case 3: {
            if (platforms.empty() || platforms.back()->GetGames().empty()) {
                std::cout << "No games available. Please create a game first.\n";
                break;
            }
            std::string title, description;
            int scoreValue;
            std::cout << "Enter achievement title: ";
            std::cin >> title;
            std::cout << "Enter achievement description: ";
            std::cin >> description;
            std::cout << "Enter achievement score value: ";
            std::cin >> scoreValue;
            platforms.back()->GetGames().back()->AddAchievement(std::make_shared<Achievement>(title, description, scoreValue));
            break;
        }
        case 4: {
            for (const auto& platform : platforms) {
                std::cout << "Platform: " << platform->GetName() << ", Manufacturer: " << platform->GetName() << std::endl;
                for (const auto& game : platform->GetGames()) {
                    std::cout << "\tGame: " << game->GetName() << ", Publisher: " << game->GetName() << ", Developer: " << game->GetName() << std::endl;
                    for (const auto& achievement : game->GetAchievements()) {
                        std::cout << "\t\tAchievement: " << achievement->GetTitle() << ", Description: " << achievement->GetDescription() << ", Score: " << achievement->GetScoreValue() << std::endl;
                    }
                }
            }
            break;
        }
        case 5: {
            std::cout << "Exiting..." << std::endl;
            return 0;
        }
        default:
            std::cout << "Invalid choice, please try again." << std::endl;
        }
    }

    return 0;
}

#include "Menu.h"
#include "Utils.h" // Для find... функций
#include "FileManager.h" // Для saveToFile в каждом меню (хотя лучше сохранять только при выходе из главного)
#include <iostream>
#include <limits>    // Для std::numeric_limits
#include <sstream>   // Для std::stringstream в editServicesMenu
#define NOMINMAX
#include <windows.h> // Для SetConsoleCP/OutputCP

// Вспомогательная функция для безопасного ввода числа
int getIntInput() {
    int choice;
    while (!(std::cin >> choice)) {
        std::cout << "Неверный ввод. Пожалуйста, введите число: ";
        std::cin.clear();
        std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
    }
    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n'); // Очистка буфера после числа
    return choice;
}

std::string getStringInput(const std::string& prompt) {
    std::cout << prompt;
    std::string input;
    std::getline(std::cin, input);
    return input;
}


void showMainMenu() {
    std::cout << "\n==== Главное меню ====\n";
    std::cout << "1. Гости\n";
    std::cout << "2. Номера\n";
    std::cout << "3. Бронирование\n";
    std::cout << "4. Оплата\n";
    std::cout << "5. Сотрудники\n";
    std::cout << "0. Выход\n";
    std::cout << "Выберите действие: ";
}

void guestMenu(std::vector<Guest>& guests) {
    int choice;
    do {
        std::cout << "\n==== Меню гостей ====\n";
        std::cout << "1. Вывести информацию о гостях\n";
        std::cout << "2. Изменить контактную информацию\n";
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (guests.empty()) {
                std::cout << "Список гостей пуст.\n";
                break;
            }
            for (const auto& g : guests) {
                g.displayInfo();
            }
            break;
        }
        case 2: {
            if (guests.empty()) {
                std::cout << "Список гостей пуст.\n";
                break;
            }
            std::cout << "Текущие гости:\n";
            for (const auto& g : guests) {
                g.displayInfo();
            }
            std::cout << "Введите ID гостя для изменения: ";
            int id = getIntInput();
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                std::string phone = getStringInput("Введите новый телефон: ");
                std::string email = getStringInput("Введите новый email: ");
                guest->updateContactInfo(phone, email);
                std::cout << "Контактная информация обновлена.\n";
            } else {
                std::cout << "Гость с ID " << id << " не найден.\n";
            }
            break;
        }
        case 0:
            saveToFile<Guest>("Guest.txt", guests); // Сохраняем при выходе из подменю
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void roomMenu(std::vector<Room>& rooms, std::vector<RoomCategory>& categories) {
    int choice;
    do {
        std::cout << "\n==== Меню номеров ====\n";
        std::cout << "1. Показать все номера\n";
        std::cout << "2. Изменить статус доступности номера\n";
        std::cout << "3. Просмотреть категории номеров\n";
        std::cout << "4. Изменить список услуг для категории\n";
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (rooms.empty()) {
                std::cout << "Список номеров пуст.\n";
                break;
            }
            std::cout << "Список номеров:\n";
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    std::cout << "Room #: " << r.getRoomNumber() << " (Категория ID: " << r.getCategoryId() << " не найдена)" << std::endl;
            }
            break;
        case 2: {
            if (rooms.empty()) {
                std::cout << "Список номеров пуст.\n";
                break;
            }
            std::cout << "Текущие номера:\n";
             for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat) r.displayDetails(*cat); else std::cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)\n";
            }
            std::cout << "Введите номер комнаты для изменения статуса: ";
            int number = getIntInput();
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                std::cout << "Текущий статус: " << (room->getAvailability() ? "Доступен" : "Занят") << std::endl;
                std::cout << "Введите новый статус (1 - доступен, 0 - занят): ";
                int statusInput = getIntInput();
                if (statusInput == 0 || statusInput == 1) {
                    room->updateStatus(statusInput != 0);
                    std::cout << "Статус обновлен.\n";
                } else {
                    std::cout << "Неверный ввод статуса.\n";
                }
            } else {
                std::cout << "Комната с номером " << number << " не найдена.\n";
            }
            break;
        }
        case 3:
            categorySubMenu(categories);
            break;
        case 4:
            editServicesMenu(categories);
            break;
        case 0:
            saveToFile<Room>("Room.txt", rooms);
            saveToFile<RoomCategory>("RoomCategory.txt", categories);
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void categorySubMenu(std::vector<RoomCategory>& categories) {
    std::cout << "\n==== Категории номеров ====\n";
    if (categories.empty()) {
        std::cout << "Нет категорий номеров.\n";
        return;
    }
    for (const auto& c : categories) {
        std::cout << "ID: " << c.getId()
                  << ", Название: " << c.getName()
                  << ", Описание: " << c.getDescription()
                  << std::endl;
        std::cout << "  Услуги:\n";
        c.printServices();
    }
}

void editServicesMenu(std::vector<RoomCategory>& categories) {
    if (categories.empty()) {
        std::cout << "Нет категорий для редактирования.\n";
        return;
    }
    std::cout << "\n==== Изменить список услуг ====\n";
    std::cout << "Список категорий:\n";
    for (const auto& c : categories) {
        std::cout << "ID: " << c.getId() << ", Название: " << c.getName() << std::endl;
    }
    std::cout << "Введите ID категории для изменения услуг: ";
    int id = getIntInput();
    RoomCategory* category = findCategoryById(categories, id);

    if (!category) {
        std::cout << "Категория с ID " << id << " не найдена.\n";
        return;
    }

    std::cout << "Текущие услуги для категории '" << category->getName() << "':\n";
    category->printServices();
    
    std::string line = getStringInput("Введите новые услуги через запятую (например: WiFi,Минибар,Завтрак). Для удаления всех услуг введите пустую строку: ");

    std::vector<std::string> newServices;
    if (!line.empty()) {
        std::stringstream ss(line);
        std::string token;
        while (std::getline(ss, token, ',')) {
            // Удаляем лишние пробелы в начале и конце токена
            size_t first = token.find_first_not_of(' ');
            if (std::string::npos == first) { // Если строка пуста или только из пробелов
                continue;
            }
            size_t last = token.find_last_not_of(' ');
            newServices.push_back(token.substr(first, (last - first + 1)));
        }
    }
    category->setServices(newServices);
    std::cout << "Список услуг обновлен.\n";
}

void bookingMenu(std::vector<Guest>& guests, std::vector<Room>& rooms, std::vector<Booking>& bookings, std::vector<RoomCategory>& categories) {
    int choice;
    do {
        std::cout << "\n==== Меню бронирования ====\n";
        std::cout << "1. Показать все бронирования\n";
        std::cout << "2. Создать новое бронирование\n";
        std::cout << "3. Отменить бронирование\n";
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (bookings.empty()) {
                std::cout << "Нет активных или завершенных бронирований.\n";
                break;
            }
            std::cout << "Список бронирований:\n";
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                } else {
                    std::cout << "Ошибка: Не удалось найти гостя или комнату для бронирования ID: " << b.getID() << std::endl;
                }
            }
            break;
        }
        case 2: {
            std::string name = getStringInput("Введите ФИО гостя: ");
            std::string phone = getStringInput("Телефон: ");
            std::string email = getStringInput("Email: ");
            std::string passport = getStringInput("Паспортные данные: ");
            
            Guest newGuest(Guest::guestCounter, name, phone, email, passport); // Используем статический счетчик
            guests.push_back(newGuest);
            Guest::guestCounter++; // Увеличиваем счетчик вручную после успешного добавления
            saveToFile<Guest>("Guest.txt", guests); // Сразу сохраняем нового гостя


            std::cout << "Доступные номера для бронирования:\n";
            bool availableRoomsExist = false;
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat) r.displayDetails(*cat);
                    else std::cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)\n";
                    availableRoomsExist = true;
                }
            }
            if (!availableRoomsExist) {
                std::cout << "Нет доступных номеров для бронирования.\n";
                // Возможно, стоит удалить только что созданного гостя, если нет номеров
                // guests.pop_back(); // Раскомментировать, если такая логика нужна
                break;
            }

            std::cout << "Выберите номер комнаты для бронирования: ";
            int roomNumber = getIntInput();
            Room* selectedRoom = findRoomByNumber(rooms, roomNumber);

            if (!selectedRoom || !selectedRoom->getAvailability()) {
                std::cout << "Комната не найдена или уже занята.\n";
                // guests.pop_back(); // Если гость создавался только для этого бронирования
                break;
            }

            std::string checkIn = getStringInput("Дата въезда (ДД.ММ.ГГГГ): ");
            std::string checkOut = getStringInput("Дата выезда (ДД.ММ.ГГГГ): ");

            Booking newBooking(newGuest, *selectedRoom, checkIn, checkOut);
            // newBooking.confirmBooking(); // Статус "Активно" уже устанавливается в конструкторе
            selectedRoom->updateStatus(false); // Комната становится недоступной
            bookings.push_back(newBooking);
            
            std::cout << "Бронирование создано успешно. ID бронирования: " << newBooking.getID() << std::endl;
            break;
        }
        case 3: {
            if (bookings.empty()) {
                std::cout << "Нет бронирований для отмены.\n";
                break;
            }
            std::cout << "Активные бронирования:\n";
            bool activeBookingsExist = false;
            for (const auto& b : bookings) {
                 if (b.getStatus() == "Активно") {
                    Guest* guest = findGuestById(guests, b.getGuestId());
                    Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                    if (guest && room) b.display(*guest, *room);
                    activeBookingsExist = true;
                 }
            }
            if (!activeBookingsExist) {
                 std::cout << "Нет активных бронирований для отмены.\n";
                 break;
            }

            std::cout << "Введите ID бронирования для отмены: ";
            int id = getIntInput();
            Booking* bookingToCancel = findBookingById(bookings, id);

            if (bookingToCancel && bookingToCancel->getStatus() == "Активно") {
                Room* roomToFree = findRoomByNumber(rooms, bookingToCancel->getRoomNumber());
                if (roomToFree) {
                    roomToFree->updateStatus(true); // Комната снова доступна
                }
                bookingToCancel->cancelBooking(); // Меняем статус бронирования
                std::cout << "Бронирование ID " << id << " отменено.\n";
            } else {
                std::cout << "Бронирование с ID " << id << " не найдено или не является активным.\n";
            }
            break;
        }
        case 0:
            saveToFile<Booking>("Booking.txt", bookings);
            saveToFile<Room>("Room.txt", rooms); // Статус комнат мог измениться
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void paymentMenu(std::vector<Booking>& bookings, std::vector<Payment>& payments, const std::vector<Room>& rooms) {
    int choice;
    do {
        std::cout << "\n==== Меню оплаты ====\n";
        std::cout << "1. Провести оплату за бронирование\n";
        std::cout << "2. Показать все квитанции об оплате\n";
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            std::cout << "Активные бронирования для оплаты:\n";
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() == "Активно") { // Оплачивать можно только активные
                     // Для отображения деталей может потребоваться вектор guests
                    std::cout << "ID бронирования: " << b.getID() 
                              << ", Номер комнаты: " << b.getRoomNumber() 
                              //<< ", Гость ID: " << b.getGuestId() // Если нужно больше информации
                              << std::endl;
                    activeBookingExists = true;
                }
            }
            if (!activeBookingExists) {
                std::cout << "Нет активных бронирований для оплаты.\n";
                break;
            }

            std::cout << "Введите ID бронирования для оплаты: ";
            int bookingId = getIntInput();
            Booking* bookingToPay = findBookingById(bookings, bookingId);

            if (bookingToPay && bookingToPay->getStatus() == "Активно") {
                const Room* roomOfBooking = nullptr;
                for(const auto& r : rooms){
                    if(r.getRoomNumber() == bookingToPay->getRoomNumber()){
                        roomOfBooking = &r;
                        break;
                    }
                }

                double cost = 0.0;
                if (roomOfBooking) {
                     // Здесь можно улучшить логику расчета, если calculateCost будет использовать даты из bookingToPay
                    cost = bookingToPay->calculateCost(roomOfBooking->getPrice()); 
                    std::cout << "Ориентировочная стоимость проживания: " << cost << " руб." << std::endl;
                } else {
                    std::cout << "Ошибка: не удалось найти комнату для расчета стоимости." << std::endl;
                    // Можно предложить ввести сумму вручную или прервать операцию
                }


                std::cout << "Введите сумму оплаты: ";
                double amount;
                while (!(std::cin >> amount) || amount <= 0) {
                    std::cout << "Неверная сумма. Введите положительное число: ";
                    std::cin.clear();
                    std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');
                }
                std::cin.ignore((std::numeric_limits<std::streamsize>::max)(), '\n');


                std::string method = getStringInput("Введите способ оплаты (наличные, карта): ");
                std::string date = getStringInput("Введите дату оплаты (ДД.ММ.ГГГГ): ");

                Payment newPayment(*bookingToPay, amount, method, date);
                newPayment.processPayment(); // Вывод информации об обработке
                payments.push_back(newPayment);
                
                bookingToPay->completeBooking(); // Меняем статус бронирования на "Завершено"
                // Статус комнаты (isAvailable) не меняем, т.к. она может быть забронирована следующим гостем.
                // Освобождение комнаты должно происходить при выезде (или отмене).
                // Если "Завершено" означает, что гость выехал, то комнату нужно освободить.
                // Room* roomToUpdate = findRoomByNumber(rooms, bookingToPay->getRoomNumber());
                // if(roomToUpdate) roomToUpdate->updateStatus(true);


                std::cout << "Оплата проведена. Статус бронирования ID " << bookingId << " изменен на 'Завершено'.\n";
            } else {
                std::cout << "Бронирование с ID " << bookingId << " не найдено или не является активным для оплаты.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                std::cout << "Квитанций об оплате нет.\n";
                break;
            }
            std::cout << "Все квитанции об оплате:\n";
            for (const auto& p : payments) {
                p.printReceipt();
            }
            break;
        }
        case 0:
            saveToFile<Payment>("Payment.txt", payments);
            saveToFile<Booking>("Booking.txt", bookings); // Статус бронирований мог измениться
            // saveToFile<Room>("Room.txt", rooms); // Если меняли статус комнат
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void employeeMenu(std::vector<Employee>& employees) {
    // В оригинальном коде это меню просто выводило список и ошибку.
    // Сделаем его более функциональным, если потребуется.
    // Пока что оставим как есть для соответствия.
    // TODO: Реализовать полноценное меню для сотрудников (добавление, удаление, редактирование)
    int choice;
     do {
        std::cout << "\n==== Меню сотрудников ====\n";
        std::cout << "1. Показать всех сотрудников\n";
        std::cout << "2. Добавить нового сотрудника\n";
        // Добавить другие опции: удалить, редактировать...
        std::cout << "0. Назад в главное меню\n";
        std::cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (employees.empty()) {
                std::cout << "Список сотрудников пуст.\n";
            } else {
                std::cout << "Список сотрудников:\n";
                for (const auto& e : employees) {
                    e.displayInfo();
                }
            }
            break;
        case 2: {
            std::string name = getStringInput("Введите ФИО сотрудника: ");
            std::string phone = getStringInput("Телефон: ");
            std::string email = getStringInput("Email: ");
            std::string position = getStringInput("Должность: ");

            Employee newEmployee(Employee::employeeCounter, name, phone, email, position);
            employees.push_back(newEmployee);
            Employee::employeeCounter++;
            std::cout << "Сотрудник добавлен. ID: " << newEmployee.getId() << std::endl;
            break;
        }
        case 0:
            saveToFile<Employee>("Employee.txt", employees);
            break;
        default:
            std::cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
}
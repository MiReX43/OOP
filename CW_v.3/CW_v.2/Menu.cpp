#include "Menu.h"
#include "Utils.h" // Для find... функций
#include "FileManager.h" // Для saveToFile в каждом меню (хотя лучше сохранять только при выходе из главного)
#include <iostream>
#include <limits>    // Для numeric_limits
#include <sstream>   // Для stringstream в editServicesMenu
#define NOMINMAX
#include <windows.h> // Для SetConsoleCP/OutputCP

using namespace std;

// Вспомогательная функция для безопасного ввода числа
int getIntInput() {
    int choice;
    while (!(cin >> choice)) {
        cout << "Неверный ввод. Пожалуйста, введите число: ";
        cin.clear();
        cin.ignore((numeric_limits<streamsize>::max)(), '\n');
    }
    cin.ignore((numeric_limits<streamsize>::max)(), '\n'); // Очистка буфера после числа
    return choice;
}

string getStringInput(const string& prompt) {
    cout << prompt;
    string input;
    getline(cin, input);
    return input;
}


void showMainMenu() {
    cout << "\n==== Главное меню ====\n";
    cout << "1. Гости\n";
    cout << "2. Номера\n";
    cout << "3. Бронирование\n";
    cout << "4. Оплата\n";
    cout << "5. Сотрудники\n";
    cout << "0. Выход\n";
    cout << "Выберите действие: ";
}

void guestMenu(vector<Guest>& guests) {
    int choice;
    do {
        cout << "\n==== Меню гостей ====\n";
        cout << "1. Вывести информацию о гостях\n";
        cout << "2. Изменить контактную информацию\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (guests.empty()) {
                cout << "Список гостей пуст.\n";
                break;
            }
            for (const auto& g : guests) {
                g.displayInfo();
            }
            break;
        }
        case 2: {
            if (guests.empty()) {
                cout << "Список гостей пуст.\n";
                break;
            }
            cout << "Текущие гости:\n";
            for (const auto& g : guests) {
                g.displayInfo();
            }
            cout << "Введите ID гостя для изменения: ";
            int id = getIntInput();
            Guest* guest = findGuestById(guests, id);
            if (guest) {
                string phone = getStringInput("Введите новый телефон: ");
                string email = getStringInput("Введите новый email: ");
                guest->updateContactInfo(phone, email);
                cout << "Контактная информация обновлена.\n";
            } else {
                cout << "Гость с ID " << id << " не найден.\n";
            }
            break;
        }
        case 0:
            saveToFile<Guest>("Guest.txt", guests); // Сохраняем при выходе из подменю
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void roomMenu(vector<Room>& rooms, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== Меню номеров ====\n";
        cout << "1. Показать все номера\n";
        cout << "2. Изменить статус доступности номера\n";
        cout << "3. Просмотреть категории номеров\n";
        cout << "4. Изменить список услуг для категории\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (rooms.empty()) {
                cout << "Список номеров пуст.\n";
                break;
            }
            cout << "Список номеров:\n";
            for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat)
                    r.displayDetails(*cat);
                else
                    cout << "Room #: " << r.getRoomNumber() << " (Категория ID: " << r.getCategoryId() << " не найдена)" << endl;
            }
            break;
        case 2: {
            if (rooms.empty()) {
                cout << "Список номеров пуст.\n";
                break;
            }
            cout << "Текущие номера:\n";
             for (const auto& r : rooms) {
                RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                if (cat) r.displayDetails(*cat); else cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)\n";
            }
            cout << "Введите номер комнаты для изменения статуса: ";
            int number = getIntInput();
            Room* room = findRoomByNumber(rooms, number);
            if (room) {
                cout << "Текущий статус: " << (room->getAvailability() ? "Доступен" : "Занят") << endl;
                cout << "Введите новый статус (1 - доступен, 0 - занят): ";
                int statusInput = getIntInput();
                if (statusInput == 0 || statusInput == 1) {
                    room->updateStatus(statusInput != 0);
                    cout << "Статус обновлен.\n";
                } else {
                    cout << "Неверный ввод статуса.\n";
                }
            } else {
                cout << "Комната с номером " << number << " не найдена.\n";
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
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void categorySubMenu(vector<RoomCategory>& categories) {
    cout << "\n==== Категории номеров ====\n";
    if (categories.empty()) {
        cout << "Нет категорий номеров.\n";
        return;
    }
    for (const auto& c : categories) {
        cout << "ID: " << c.getId()
                  << ", Название: " << c.getName()
                  << ", Описание: " << c.getDescription()
                  << endl;
        cout << "  Услуги:\n";
        c.printServices();
    }
}

void editServicesMenu(vector<RoomCategory>& categories) {
    if (categories.empty()) {
        cout << "Нет категорий для редактирования.\n";
        return;
    }
    cout << "\n==== Изменить список услуг ====\n";
    cout << "Список категорий:\n";
    for (const auto& c : categories) {
        cout << "ID: " << c.getId() << ", Название: " << c.getName() << endl;
    }
    cout << "Введите ID категории для изменения услуг: ";
    int id = getIntInput();
    RoomCategory* category = findCategoryById(categories, id);

    if (!category) {
        cout << "Категория с ID " << id << " не найдена.\n";
        return;
    }

    cout << "Текущие услуги для категории '" << category->getName() << "':\n";
    category->printServices();
    
    string line = getStringInput("Введите новые услуги через запятую (например: WiFi,Минибар,Завтрак). Для удаления всех услуг введите пустую строку: ");

    vector<string> newServices;
    if (!line.empty()) {
        stringstream ss(line);
        string token;
        while (getline(ss, token, ',')) {
            // Удаляем лишние пробелы в начале и конце токена
            size_t first = token.find_first_not_of(' ');
            if (string::npos == first) { // Если строка пуста или только из пробелов
                continue;
            }
            size_t last = token.find_last_not_of(' ');
            newServices.push_back(token.substr(first, (last - first + 1)));
        }
    }
    category->setServices(newServices);
    cout << "Список услуг обновлен.\n";
}

void bookingMenu(vector<Guest>& guests, vector<Room>& rooms, vector<Booking>& bookings, vector<RoomCategory>& categories) {
    int choice;
    do {
        cout << "\n==== Меню бронирования ====\n";
        cout << "1. Показать все бронирования\n";
        cout << "2. Создать новое бронирование\n";
        cout << "3. Отменить бронирование\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            if (bookings.empty()) {
                cout << "Нет активных или завершенных бронирований.\n";
                break;
            }
            cout << "Список бронирований:\n";
            for (const auto& b : bookings) {
                Guest* guest = findGuestById(guests, b.getGuestId());
                Room* room = findRoomByNumber(rooms, b.getRoomNumber());
                if (guest && room) {
                    b.display(*guest, *room);
                } else {
                    cout << "Ошибка: Не удалось найти гостя или комнату для бронирования ID: " << b.getID() << endl;
                }
            }
            break;
        }
        case 2: {
            string name = getStringInput("Введите ФИО гостя: ");
            string phone = getStringInput("Телефон: ");
            string email = getStringInput("Email: ");
            string passport = getStringInput("Паспортные данные: ");
            
            Guest newGuest(Guest::guestCounter, name, phone, email, passport); // Используем статический счетчик
            guests.push_back(newGuest);
            Guest::guestCounter++; // Увеличиваем счетчик вручную после успешного добавления
            saveToFile<Guest>("Guest.txt", guests); // Сразу сохраняем нового гостя


            cout << "Доступные номера для бронирования:\n";
            bool availableRoomsExist = false;
            for (const auto& r : rooms) {
                if (r.getAvailability()) {
                    RoomCategory* cat = findCategoryById(categories, r.getCategoryId());
                    if (cat) r.displayDetails(*cat);
                    else cout << "Room #: " << r.getRoomNumber() << " (Категория не найдена)\n";
                    availableRoomsExist = true;
                }
            }
            if (!availableRoomsExist) {
                cout << "Нет доступных номеров для бронирования.\n";
                // Возможно, стоит удалить только что созданного гостя, если нет номеров
                // guests.pop_back(); // Раскомментировать, если такая логика нужна
                break;
            }

            cout << "Выберите номер комнаты для бронирования: ";
            int roomNumber = getIntInput();
            Room* selectedRoom = findRoomByNumber(rooms, roomNumber);

            if (!selectedRoom || !selectedRoom->getAvailability()) {
                cout << "Комната не найдена или уже занята.\n";
                // guests.pop_back(); // Если гость создавался только для этого бронирования
                break;
            }

            string checkIn = getStringInput("Дата въезда (ДД.ММ.ГГГГ): ");
            string checkOut = getStringInput("Дата выезда (ДД.ММ.ГГГГ): ");

            Booking newBooking(newGuest, *selectedRoom, checkIn, checkOut);
            // newBooking.confirmBooking(); // Статус "Активно" уже устанавливается в конструкторе
            selectedRoom->updateStatus(false); // Комната становится недоступной
            bookings.push_back(newBooking);
            
            cout << "Бронирование создано успешно. ID бронирования: " << newBooking.getID() << endl;
            break;
        }
        case 3: {
            if (bookings.empty()) {
                cout << "Нет бронирований для отмены.\n";
                break;
            }
            cout << "Активные бронирования:\n";
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
                 cout << "Нет активных бронирований для отмены.\n";
                 break;
            }

            cout << "Введите ID бронирования для отмены: ";
            int id = getIntInput();
            Booking* bookingToCancel = findBookingById(bookings, id);

            if (bookingToCancel && bookingToCancel->getStatus() == "Активно") {
                Room* roomToFree = findRoomByNumber(rooms, bookingToCancel->getRoomNumber());
                if (roomToFree) {
                    roomToFree->updateStatus(true); // Комната снова доступна
                }
                bookingToCancel->cancelBooking(); // Меняем статус бронирования
                cout << "Бронирование ID " << id << " отменено.\n";
            } else {
                cout << "Бронирование с ID " << id << " не найдено или не является активным.\n";
            }
            break;
        }
        case 0:
            saveToFile<Booking>("Booking.txt", bookings);
            saveToFile<Room>("Room.txt", rooms); // Статус комнат мог измениться
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void paymentMenu(vector<Booking>& bookings, vector<Payment>& payments, const vector<Room>& rooms) {
    int choice;
    do {
        cout << "\n==== Меню оплаты ====\n";
        cout << "1. Провести оплату за бронирование\n";
        cout << "2. Показать все квитанции об оплате\n";
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1: {
            cout << "Активные бронирования для оплаты:\n";
            bool activeBookingExists = false;
            for (const auto& b : bookings) {
                if (b.getStatus() == "Активно") { // Оплачивать можно только активные
                     // Для отображения деталей может потребоваться вектор guests
                    cout << "ID бронирования: " << b.getID() 
                              << ", Номер комнаты: " << b.getRoomNumber() 
                              //<< ", Гость ID: " << b.getGuestId() // Если нужно больше информации
                              << endl;
                    activeBookingExists = true;
                }
            }
            if (!activeBookingExists) {
                cout << "Нет активных бронирований для оплаты.\n";
                break;
            }

            cout << "Введите ID бронирования для оплаты: ";
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
                    cout << "Ориентировочная стоимость проживания: " << cost << " руб." << endl;
                } else {
                    cout << "Ошибка: не удалось найти комнату для расчета стоимости." << endl;
                    // Можно предложить ввести сумму вручную или прервать операцию
                }


                cout << "Введите сумму оплаты: ";
                double amount;
                while (!(cin >> amount) || amount <= 0) {
                    cout << "Неверная сумма. Введите положительное число: ";
                    cin.clear();
                    cin.ignore((numeric_limits<streamsize>::max)(), '\n');
                }
                cin.ignore((numeric_limits<streamsize>::max)(), '\n');


                string method = getStringInput("Введите способ оплаты (наличные, карта): ");
                string date = getStringInput("Введите дату оплаты (ДД.ММ.ГГГГ): ");

                Payment newPayment(*bookingToPay, amount, method, date);
                newPayment.processPayment(); // Вывод информации об обработке
                payments.push_back(newPayment);
                
                bookingToPay->completeBooking(); // Меняем статус бронирования на "Завершено"
                // Статус комнаты (isAvailable) не меняем, т.к. она может быть забронирована следующим гостем.
                // Освобождение комнаты должно происходить при выезде (или отмене).
                // Если "Завершено" означает, что гость выехал, то комнату нужно освободить.
                // Room* roomToUpdate = findRoomByNumber(rooms, bookingToPay->getRoomNumber());
                // if(roomToUpdate) roomToUpdate->updateStatus(true);


                cout << "Оплата проведена. Статус бронирования ID " << bookingId << " изменен на 'Завершено'.\n";
            } else {
                cout << "Бронирование с ID " << bookingId << " не найдено или не является активным для оплаты.\n";
            }
            break;
        }
        case 2: {
            if (payments.empty()) {
                cout << "Квитанций об оплате нет.\n";
                break;
            }
            cout << "Все квитанции об оплате:\n";
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
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
}

void employeeMenu(vector<Employee>& employees) {
    // В оригинальном коде это меню просто выводило список и ошибку.
    // Сделаем его более функциональным, если потребуется.
    // Пока что оставим как есть для соответствия.
    // TODO: Реализовать полноценное меню для сотрудников (добавление, удаление, редактирование)
    int choice;
     do {
        cout << "\n==== Меню сотрудников ====\n";
        cout << "1. Показать всех сотрудников\n";
        cout << "2. Добавить нового сотрудника\n";
        // Добавить другие опции: удалить, редактировать...
        cout << "0. Назад в главное меню\n";
        cout << "Выберите действие: ";
        choice = getIntInput();

        switch (choice) {
        case 1:
            if (employees.empty()) {
                cout << "Список сотрудников пуст.\n";
            } else {
                cout << "Список сотрудников:\n";
                for (const auto& e : employees) {
                    e.displayInfo();
                }
            }
            break;
        case 2: {
            string name = getStringInput("Введите ФИО сотрудника: ");
            string phone = getStringInput("Телефон: ");
            string email = getStringInput("Email: ");
            string position = getStringInput("Должность: ");

            Employee newEmployee(Employee::employeeCounter, name, phone, email, position);
            employees.push_back(newEmployee);
            Employee::employeeCounter++;
            cout << "Сотрудник добавлен. ID: " << newEmployee.getId() << endl;
            break;
        }
        case 0:
            saveToFile<Employee>("Employee.txt", employees);
            break;
        default:
            cout << "Неверный выбор. Попробуйте снова.\n";
        }
    } while (choice != 0);
    
}
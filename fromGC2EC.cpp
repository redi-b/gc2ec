#include <iomanip>
#include <iostream>

using namespace std;

int main()
{
    int targetYear;

    do
    {
        bool isJulian, isLeapYear[2]; // 0 - Gregorian, 1 - Ethiopian
        int ethiopianDates[366];

        cout << "Enter year: ";
        cin >> targetYear;

        if (targetYear <= 0)
        {
            cout << "Invalid year!" << endl;
            continue;
        }

        int etStartYear = targetYear - 8, etEndYear = targetYear - 7;
        if (targetYear <= 8)
            etStartYear = 0, etEndYear = 0;

        isJulian = (targetYear <= 1752);
        isLeapYear[0] = (targetYear % 4 == 0) &&
                        (targetYear % 100 != 0 || targetYear % 400 == 0);
        isLeapYear[1] =
            ((targetYear + 1) % 4 == 0) &&
            ((targetYear + 1) % 100 != 0 || (targetYear + 1) % 400 == 0);

        int dayOffset = 0;

        if (targetYear < 1900)
            dayOffset = 1;
        else if (targetYear > 2100)
            dayOffset = -1;

        int ethiopianMonth = 4;            // Corresponds to January in EC
        int ethiopianDay = 23 + dayOffset; // Corresponds to January 1 in EC

        if (isJulian)
        {
            isLeapYear[0] = (targetYear % 4 == 0);
            isLeapYear[1] = ((targetYear + 1) % 4) == 0;
            if (isLeapYear[0])
                dayOffset = 2;
            else
                dayOffset = 3;
            ethiopianMonth = 5; // Corresponds to January in EC if the year is in JC
            ethiopianDay = 6;   // Corresponds to January 1 in EC if the year is in JC
        }

        if (isLeapYear[0] && !isJulian)
            ethiopianDay = 22 + dayOffset;

        int gregorianMonthLengths[] = {31, 28, 31, 30, 31, 30,
                                       31, 31, 30, 31, 30, 31};
        if (isLeapYear[0])
            gregorianMonthLengths[1] = 29; // February during leap year

        if (targetYear == 1752)
            gregorianMonthLengths[8] = 19; // 1752

        string gregorianMonthNames[] = {"January", "February", "March",
                                        "April", "May", "June",
                                        "July", "August", "September",
                                        "October", "November", "December"};

        string etMonthNamesGC[] = {
            "Tahisas-Tir", "Tir-Yekatit", "Yekatit-Megabit",
            "Megabit-Meyazia", "Meyazia-Ginbot", "Ginbot-Sene",
            "Sene-Hamle", "Hamle-Nehase", "Nehase-Pagume-Meskerem",
            "Meskerem-Tikimt", "Tikimt-Hidar", "Hidar-Tahisas"};

        string etMonthNamesJC[] = {"Tir-Yekatit", "Yekatit-Megabit",
                                   "Megabit-Meyazia", "Meyazia-Ginbot",
                                   "Ginbot-Sene", "Sene-Hamle",
                                   "Hamle-Nehase", "Nehase-Pagume-Meskerem",
                                   "Meskerem-Tikimt", "Tikimt-Hidar",
                                   "Hidar-Tahisas", "Tahisas-Tir"};
        if (targetYear == 1752)
            etMonthNamesJC[8] = "Meskerem";

        string ethiopianMonthNames[12];
        for (int i = 0; i < 12; i++)
            if (targetYear < 8)
                ethiopianMonthNames[i] = "";
            else if (isJulian)
                ethiopianMonthNames[i] = etMonthNamesJC[i];
            else
                ethiopianMonthNames[i] = etMonthNamesGC[i];
P
        for (int i = 0; i < 366; i++)
        {
            ethiopianDates[i] = ethiopianDay;
            ethiopianDay++;
            if (ethiopianMonth == 13 &&
                ((!isLeapYear[1] && ethiopianDay == 6) || (isLeapYear[1] && ethiopianDay == 7)))
            {
                ethiopianDay = 1;
                ethiopianMonth = 1;
            }
            if (ethiopianDay > 30)
            {
                ethiopianDay = 1;
                ethiopianMonth++;
            }
        }

        // sYY - first two digits of year
        // eYY - last two digits of year
        // YC - year code
        // CC - century code
        // LYC - leap year code
        int sYY, eYY, YC, CC, LYC;
        int MC[] = {0, 3, 3, 6, 1, 4, 6, 2, 5, 0, 3, 5};
        int startDays[12];

        sYY = targetYear / 100;
        eYY = targetYear % 100;
        YC = (eYY + (eYY / 4)) % 7;
        if (isJulian)
            CC = (18 - (sYY)) % 7;
        else
            CC = (3 - (sYY % 4)) * 2;
        for (int i = 0; i < 12; i++)
        {
            if (isLeapYear[0] && i < 2)
                LYC = -1;
            else
                LYC = 0;
            startDays[i] = (YC + MC[i] + CC + 1 + LYC) % 7;
        }

        string daysOfTheWeek[] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};

        int cumulativeDays = 0;
        for (int month = 0; month < 12; month++)
        {
            cout << "\nYear: " << targetYear << "\t\t";
            cout << "Ethiopian Years: ";
            cout << etStartYear << " - " << etEndYear << endl;
            cout << gregorianMonthNames[month] << "\t\t";
            cout << ethiopianMonthNames[month] << endl;
            cout << setw(1) << "|" << string(48, '-') << "|" << endl;
            for (int i = 0; i < 7; i++)
                cout << "|" << setw(6) << daysOfTheWeek[i];
            cout << setw(1) << "|" << endl;
            cout << setw(1) << "|" << string(48, '-') << "|" << endl;

            int dayOfMonth = 1;
            int numOfWeeks =
                (startDays[month] + gregorianMonthLengths[month] + 6) /
                7;
            int ecPrintBack = 7;

            for (int week = 0; week < numOfWeeks; week++)
            {
                if (week == (numOfWeeks - 1))
                    ecPrintBack =
                        ((startDays[month] + gregorianMonthLengths[month] - 1) %
                         7) +
                        1;

                cout << "|";

                for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++)
                {
                    if ((week == 0 && dayOfWeek < startDays[month]) ||
                        dayOfMonth > gregorianMonthLengths[month])
                    {
                        cout << "      |";
                    }
                    else
                    {
                        if (targetYear == 1752 && month == 8 && dayOfMonth >= 3)
                            cout << setw(6) << right << dayOfMonth + 11
                                 << "|"; // 1752
                        else
                            cout << setw(6) << right << dayOfMonth << "|";
                        dayOfMonth++;
                    }
                }
                cout << endl;
                if (targetYear > 8)
                {
                    cout << "|";
                    dayOfMonth -= ecPrintBack;

                    for (int dayOfWeek = 0; dayOfWeek < 7; dayOfWeek++)
                    {
                        if ((week == 0 && dayOfWeek < startDays[month]) ||
                            dayOfMonth > gregorianMonthLengths[month])
                        {
                            cout << "      |";
                            dayOfMonth++;
                        }
                        else
                        {
                            cout << setw(6) << left
                                 << ethiopianDates[cumulativeDays + dayOfMonth -
                                                   1]
                                 << "|";
                            dayOfMonth++;
                        }
                    }
                    cout << endl;
                }

                cout << setw(1) << "|" << string(48, '-') << "|" << endl;
            }
            cumulativeDays += gregorianMonthLengths[month];
        }

    } while (targetYear != 0);

    return 0;
}

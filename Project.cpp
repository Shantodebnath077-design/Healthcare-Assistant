#include <bits/stdc++.h>
using namespace std;
#define RT "\033[31m"
#define GT "\033[32m"
#define BT "\033[36m"
#define YT "\033[33m"
#define RET "\033[0m"
void HealthIndices(float weight, float height_cm, float waist, int age, char gender, float &bmi, float &whtr, float &ibws, float &ibwe, float &bodyfat, string &nutrition)
{
    float height_m = height_cm / 100.0;

    bmi = weight / (height_m * height_m);

    whtr = waist / height_cm;

    float height_inch = height_cm / 2.54;
    ibws = 18.5 * height_m * height_m;
    ibwe = 24.9 * height_m * height_m;
    int g = (gender == 'm' || gender == 'M') ? 1 : 0;
    if (age > 19)
        bodyfat = (1.20 * bmi) + (0.23 * age) - (10.8 * g) - 5.4;
    else
        bodyfat = (1.51 * bmi) - (0.70 * age) - (3.6 * g) + 1.4;
    if (bmi < 16)
        nutrition = "\033[31mSevere_Malnutrition\033[0m";
    else if (bmi < 17)
        nutrition = "\033[31mModerate_Malnutrition\033[0m";
    else if (bmi < 18.5)
        nutrition = "\033[31mMild_Malnutrition\033[0m";
    else if (bmi < 25)
        nutrition = "\033[32mNormal\033[0m";
    else
        nutrition = "\033[31mHyperalimentation\033[0m";
}
void saveData(string username, int age, float bmi, float whtr, float ibws, float ibwe, float bodyfat, string nutrition)
{
    vector<string> allLines;
    vector<string> userLines;
    ifstream in("health_data.txt");
    string line, user;
    while (getline(in, line))
    {
        stringstream ss(line);
        ss >> user;
        if (user == username)
            userLines.push_back(line);
        else
            allLines.push_back(line);
    }
    in.close();
    while (userLines.size() >= 5)
        userLines.erase(userLines.begin());
    string nutrition_fixed = nutrition;
    replace(nutrition_fixed.begin(), nutrition_fixed.end(), ' ', '_');
    time_t now = time(0);
    tm *ltm = localtime(&now);
    string dateTime =
        to_string(1900 + ltm->tm_year) + "-" +
        to_string(1 + ltm->tm_mon) + "-" +
        to_string(ltm->tm_mday) + "&" +
        to_string(ltm->tm_hour) + ":" +
        to_string(ltm->tm_min);
    string newRecord =
        username + " " +
        dateTime + " " +
        to_string(age) + " " +
        to_string(bmi) + " " +
        to_string(whtr) + " " +
        to_string(ibws) + " " +
        to_string(ibwe) + " " +
        to_string(bodyfat) + " " +
        nutrition_fixed;
    userLines.push_back(newRecord);
    ofstream out("health_data.txt");
    for (string l : allLines)
        out << l << endl;
    for (string l : userLines)
        out << l << endl;
    out.close();
}
void showData(string username)
{
    ifstream in("health_data.txt");
    string u, nutrition, dateTime;
    int age;
    float bmi, whtr, ibws, ibwe, bodyfat;
    bool found = false;
    cout << BT << "--------Your saved data-------" << RET << endl;
    while (in >> u >> dateTime >> age >> bmi >> whtr >> ibws >> ibwe >> bodyfat >> nutrition)
    {
        if (u == username)
        {
            found = true;
            replace(nutrition.begin(), nutrition.end(), '_', ' ');
            replace(dateTime.begin(), dateTime.end(), '&', ' ');
            cout << YT << "Date & Time: " << dateTime << RET << endl;
            if (bmi >= 18.5 && bmi <= 24.9)
                cout << "BMI (Body Mass Index): " << GT << fixed << setprecision(1) << bmi << RET << endl;
            else
                cout << "BMI (Body Mass Index): " << RT << fixed << setprecision(1) << bmi << RET << endl;
            if (whtr < 0.5)
                cout << "WHtR (Waist-to-Height Ratio): " << GT << fixed << setprecision(1) << whtr << RET << endl;
            else
                cout << "WHtR (Waist-to-Height Ratio): " << RT << fixed << setprecision(1) << whtr << RET << endl;
            if (bodyfat > 25)
                cout << "Body Fat: " << RT << fixed << setprecision(2) << bodyfat << " %" << RET << endl;
            else
                cout << "Body Fat: " << GT << fixed << setprecision(2) << bodyfat << " %" << RET << endl;
            cout << "Ideal Body Weight: " << GT << fixed << setprecision(2) << ibws << RET << " to " << GT << fixed << setprecision(2) << ibwe << " kg" << RET << endl;
            cout << "Nutrition Status: " << nutrition << endl;
        }
    }
    in.close();
    if (!found)
    {
        cout << RT << "You do not have any saved data!" << RET << endl;
    }
}
void healthAdvice(float bmi, float whtr, float bodyfat, char gender, int age)
{
    cout << BT << "\n----- Health Recommendations -----" << RET << endl;
    // BMI advice
    if (bmi < 18.5)
        cout << RT << "# Your BMI is low and you are underweight. Eat foods high in healthy fats and proteins.\n  Incorporate strength training to ensure weight gain is muscle, not just fat." << RET << endl;
    else if (bmi < 25)
        cout << GT << "# Your BMI is normal. Maintain a balanced diet and regular exercise." << RET << endl;
    else if (bmi < 30)
        cout << RT << "# Your BMI is high and you are overweight. Try regular exercise and reduce sugary foods.\n  Prioritize high-fiber vegetables and lean protein to increase satiety.Walking at least 7,000-10,000 steps a day." << RET << endl;
    else
        cout << RT << "# Your BMI is very high and Obesity risk detected. Consult a doctor and start a structured fitness plan." << RET << endl;
    // WHtR advice
    if (whtr >= 0.50)
    {
        cout << RT << "# Your WHtR is high. This indicates abdominal fat and increased cardiovascular risk." << RET << endl;
        cout << RT << "# Reduce waist through cardio exercises, core strengthening, and healthy diet." << RET << endl;
    }
    else
        cout << GT << "# Your WHtR is within healthy range." << RET << endl;
    // Body fat advice
    if (age > 19 && bodyfat > 25)
        cout << RT << "# Body fat is high. Increase physical activity and eat healthy foods." << RET << endl;
    if (age < 19 && bodyfat > 20)
        cout << RT << "# Body fat is high.Increase physical activity at least 60 minutes/day,limit screen time,ensure proper sleep." << RET << endl;
    if (gender == 'm' || gender == 'M')
        cout << GT << "# Drink enough water(3.1 liters) daily ." << RET << endl;
    else
        cout << GT << "# Drink enough water(2.1 liters) daily." << RET << endl;
    cout << GT << "# Sleep 7-8 hours regularly." << RET << endl;
}
void weightAdjustment(float weight, float height_cm, int age, float bmi)
{
    float height_m = height_cm / 100.0;
    float minNormalWeight = 18.5 * height_m * height_m; // weight for BMI = 18.5
    float maxNormalWeight = 24.9 * height_m * height_m; // weight for BMI = 24.9
    cout << BT << "\n----- Weight Adjustment Advice -----" << RET << endl;
    if (bmi < 18.5)
    {
        float gain = minNormalWeight - weight;
        cout << "# You are" << RT << " underweight" << RET << ". Gain at least " << RT << gain << RET << " kg to reach a healthy weight." << endl;
        // Age-based suggestion
        if (age < 18)
            cout << "# Focus on growth-friendly nutrition: protein, milk, fruits, and vegetables." << endl;
        else if (age <= 60)
            cout << "# Increase calorie intake with balanced diet and strength training." << endl;
        else
            cout << "# Eat nutrient-dense foods and include moderate physical activity." << endl;
    }
    else if (bmi > 24.9)
    {
        float lose = weight - maxNormalWeight;
        cout << "# You are" << RT << " overweight" << RET << ". Lose at least " << RT << lose << RET << " kg to reach a healthy weight." << endl;
        // Age-based suggestion
        if (age < 18)
            cout << "# Focus on active lifestyle and reduce sugary/fatty foods." << endl;
        else if (age <= 60)
            cout << "# Combine cardio, strength training, and portion control." << endl;
        else
            cout << "# Light exercise and balanced diet recommended." << endl;
    }
    else
    {
        cout << GT << "# Your weight is within the healthy range. Maintain your current lifestyle." << RET << endl;
    }
}
void registerUser()
{
    string username, password;

    cout << "Enter new username: ";
    cin >> username;

    cout << "Enter new password: ";
    cin >> password;

    ofstream file("users.txt", ios::app);
    file << username << " " << password << endl;
    file.close();
    cout << GT << "-------Registration successful!-------" << RET << endl;
}
bool loginUser(string &username)
{
    string password, u, p;

    cout << "Enter username: ";
    cin >> username;

    cout << "Enter password: ";
    cin >> password;

    ifstream file("users.txt");
    while (file >> u >> p)
    {
        if (u == username && p == password)
        {
            return true;
        }
    }
    return false;
}
void chatbot(string username)
{
    cin.ignore();
    string msg, bmi_status = "";
    float bmi = -1, whtr = -1, bodyfat = -1, muac = -1, ibw = -1;
    cout << BT << "\n\n----- Health Chatbot -----" << RET << endl;
    cout << "Bot: Enter health indices (bmi, whtr, bodyfat, ibw)" << RET << endl;
    cout << "     " << "Example ---->" << YT << "bmi 24 whtr 0.48 bodyfat 22" << RET << endl;
    cout << "     " << "Then ask for" << YT << " 'lifestyle suggestion'" << RET << " or " << YT << " 'food suggestion'" << RET << endl;
    cout << "     " << "You can also" << YT << "ask about those indices" << RET << endl;
    cout << "     " << "Type" << YT << " exit" << RET << " to stop" << endl;
    while (true)
    {
    level:
        cout << "\nYou: " << YT;
        getline(cin, msg);
        cout << RET;
        cout << "Bot: ";
        string lmsg = msg;
        transform(lmsg.begin(), lmsg.end(), lmsg.begin(), ::tolower);
        if (lmsg.find("hi") != string::npos || lmsg.find("hello") != string::npos || lmsg.find("chatbot") != string::npos)
        {
            cout << "Hey! " << YT << username << RET << ", How is your health?" << endl;
            goto level;
        }
        else if (lmsg.find("well") != string::npos || lmsg.find("am good") != string::npos || lmsg.find("am fine") != string::npos)
        {
            cout << "Happy to hear that.\n     Tell me about your indices value and let me check your health condition" << endl;
            goto level;
        }
        else if (lmsg.find("not") != string::npos || lmsg.find("not well") != string::npos || lmsg.find("not fine") != string::npos)
        {
            cout << "Very sad to hear that.\n     Tell me about your indices.\n     I will help you by providing health status and suggestions." << endl;
            goto level;
        }
        if (lmsg == "exit")
        {
            cout << GT << "Stay healthy!\n"
                 << RET;
            break;
        }
        if (lmsg.find("thank") != string::npos || lmsg.find("thanks") != string::npos)
        {
            cout << GT << "Happy to help. Take care of yourself." << RET << endl;
            goto level;
        }
        if (lmsg == "bmi" || lmsg == "body mass index" || lmsg.find("what is bmi") != string::npos || lmsg.find("what is body mass index") != string::npos)
        {
            cout << "BMI (Body Mass Index) measures body weight relative to height." << endl;
            cout << "     " << "Formula -> Weight(kg) / Height(m)^2" << endl;
            cout << "     " << "It helps classify underweight, normal, overweight, and obesity." << endl;
            continue;
        }
        if (lmsg == "whtr" || lmsg == "waist to height ratio" || lmsg.find("what is whtr") != string::npos || lmsg.find("what is waist to height ratio") != string::npos)
        {
            cout << "WHtR (Waist-to-Height Ratio) compares waist size to height." << endl;
            cout << "     " << "It helps estimate abdominal fat and cardiovascular risk." << endl;
            cout << "     " << "Healthy value is usually below 0.5." << endl;
            cout << "     " << "Formula-->Waist Circumference (cm)/Height(cm)" << endl;
            continue;
        }
        if (lmsg == "bodyfat" || lmsg == "body fat" || lmsg.find("what is bodyfat") != string::npos || lmsg.find("what is body fat") != string::npos)
        {
            cout << "Body Fat Percentage represents how much of your body weight is fat." << endl;
            cout << "     " << "It helps evaluate body composition and obesity risk." << endl;
            cout << "     " << "Formula-->Body Fat %=(1.20*BMI)+(0.23*Age)-(10.8*Gender)-5.4" << endl;
            cout << "     " << "Where,Gender = 1 for male, 0 for female" << endl;
            continue;
        }
        if (lmsg == "ibw" || lmsg == "ideal body weight" || lmsg.find("what is ibw") != string::npos || lmsg.find("what is ideal body weight") != string::npos)
        {
            cout << "IBW means Ideal Body Weight." << endl;
            cout << "     " << "It represents the healthy body weight for your height." << endl;
            continue;
        }
        stringstream ss(lmsg);
        vector<string> words;
        string w;
        while (ss >> w)
            words.push_back(w);
        bool indexDetected = false;
        /* -------- DETECT INDICES -------- */
        for (int i = 0; i < words.size(); i++)
        {
            if (words[i] == "bmi" || words[i] == "whtr" || words[i] == "bodyfat" || words[i] == "ibw")
            {
                float value = -1;
                for (int j = i + 1; j < words.size(); j++)
                {
                    try
                    {
                        value = stof(words[j]);
                        break;
                    }
                    catch (...)
                    {
                    }
                }
                if (value == -1)
                    continue;
                indexDetected = true;
                if (words[i] == "bmi")
                {
                    bmi = value;
                    if (bmi < 18.5)
                        bmi_status = "\033[31mUnderweight\033[0m";
                    else if (bmi < 25)
                        bmi_status = "\033[32mNormal weight\033[0m";
                    else if (bmi < 30)
                        bmi_status = "\033[31mOverweight\033[0m";
                    else
                        bmi_status = "\033[31mObese\033[0m";
                    cout << "Your BMI is " << bmi << " -----> " << bmi_status << endl
                         << "     ";
                }
                else if (words[i] == "whtr")
                {
                    whtr = value;
                    cout << "Your WHtR is " << whtr << " -----> " << (whtr < 0.5 ? "\033[32mHealthy\033[0m" : "\033[31mHigh Risk\033[0m") << endl
                         << "     ";
                }
                else if (words[i] == "bodyfat")
                {
                    bodyfat = value;
                    cout << "Your BodyFat is " << bodyfat << " -----> " << (bodyfat <= 25 ? "\033[32mNormal\033[0m" : "\033[31mHigh\033[0m") << endl
                         << "     ";
                }
                else if (words[i] == "ibw")
                {
                    ibw = value;
                    cout << "Your IBW is (Ideal Body Weight) " << GT << ibw << " kg" << RET << endl
                         << "     ";
                }
            }
        }
        if (indexDetected)
            continue;
        /* ---------- LIFESTYLE SUGGESTION ---------- */
        if (lmsg.find("lifestyle") != string::npos || lmsg.find("life style") != string::npos || lmsg.find("do") != string::npos)
        {
            if (bmi < 18.5 && bmi != -1)
                cout << BT << "Increase calorie intake and do strength training" << RET << endl
                     << "     ";
            else if (bmi < 25 && bmi != -1)
                cout << BT << "Maintain active lifestyle and daily exercise" << RET << endl
                     << "     ";
            else if (bmi < 30 && bmi != -1)
                cout << BT << "Do cardio exercise and reduce sedentary habits" << RET << endl
                     << "     ";
            else if (bmi > 30 && bmi != -1)
                cout << BT << "Strict low-calorie diet, vegetables, lean protein, avoid fried foods, exercise daily." << RET << endl
                     << "     ";
            if (whtr > 0.5)
                cout << BT << "Reduce abdominal fat by cutting sugar/refined carbs and increasing fiber and exercise." << RET << endl
                     << "     ";
            if (bodyfat > 25)
                cout << BT << "Increase physical activity" << RET << endl
                     << "     ";
            if (bmi == -1 && whtr == -1 && bodyfat == -1)
                cout << RT << "Please provide health indices first" << RET << endl
                     << "     ";
        }
        /* ---------- FOOD SUGGESTION ---------- */
        else if (lmsg.find("food") != string::npos || lmsg.find("eat") != string::npos)
        {
            if (bmi < 18.5 && bmi != -1)
                cout << "Milk, eggs, nuts, rice, banana" << RET << endl
                     << "     ";
            else if (bmi < 25 && bmi != -1)
                cout << BT << "Fruits, vegetables, fish, whole grains" << RET << endl
                     << "     ";
            else if (bmi != -1)
                cout << BT << "Salad, oats, vegetables, lean protein" << RET << endl
                     << "     ";
            if (whtr > 0.5)
                cout << BT << "Avoid sugary drinks and fried foods" << RET << endl
                     << "     ";
            if (bodyfat > 25)
                cout << BT << "Reduce fatty foods and increase fiber" << RET << endl
                     << "     ";
            if (bmi == -1 && whtr == -1 && bodyfat == -1)
                cout << RT << "Please provide health indices first" << RET << endl
                     << "     ";
        }
        else
        {
            cout << BT << "I can analyze BMI, WHtR, BodyFat and IBW." << RET << endl
                 << "     ";
        }
    }
}
float getLastBMI(string username)
{
    ifstream in("health_data.txt");

    string u, dateTime, nutrition;
    int age;
    float bmi, whtr, ibws, ibwe, bodyfat;

    float lastBMI = -1;

    while (in >> u >> dateTime >> age >> bmi >> whtr >> ibws >> ibwe >> bodyfat >> nutrition)
    {
        if (u == username)
        {
            lastBMI = bmi;
        }
    }

    in.close();
    return lastBMI;
}
int getLastAge(string username)
{
    ifstream in("health_data.txt");

    string u, dateTime, nutrition;
    int age;
    float bmi, whtr, ibws, ibwe, bodyfat;

    int lastAge = -1;

    while (in >> u >> dateTime >> age >> bmi >> whtr >> ibws >> ibwe >> bodyfat >> nutrition)
    {
        if (u == username)
        {
            lastAge = age;
        }
    }
    in.close();
    return lastAge;
}
void dietPlan(float bmi, int age)
{
    string ageGroup;
    // -------- AGE CLASSIFICATION --------
    if (age >= 13 && age <= 18)
        ageGroup = "Teen";
    else if (age >= 19 && age <= 30)
        ageGroup = "Young Adult";
    else if (age >= 31 && age <= 60)
        ageGroup = "Adult";
    else
        ageGroup = "Senior";

    cout << YT << "================ DIET PLAN ================" << RET << endl;
    cout << BT << "Age Group: " << ageGroup << RET << endl;
    cout << BT << "BMI: " << bmi << endl
         << RET;
    if (bmi < 18.5)
    {
        cout << YT << "Goal --------- Healthy Weight Gain" << RET << endl;

        if (ageGroup == "Teen")
        {
            cout << GT << "Breakfast:" << RET << "Milk 300 ml, Eggs 2, Banana 1, Bread 2 slices\n";
            cout << GT << "Lunch:" << RET << " Rice 2 cups, Chicken/Fish 150g, Vegetables 1 cup, Dal 1 cup\n";
            cout << GT << "Dinner:" << RET << " Rice 1.5 cups, Egg curry (2 eggs), Vegetables 1 cup\n";
            cout << GT << "Snacks:" << RET << " Nuts 30g, Dates 3-5, Yogurt 100g\n";
        }

        else if (ageGroup == "Young Adult")
        {
            cout << GT << "Breakfast:" << RET << " Milk 250 ml, Eggs 2, Oats 50g, Banana 1\n";
            cout << GT << "Lunch:" << RET << " Rice 2 cups, Chicken/Fish 150g, Vegetables 1 cup\n";
            cout << GT << "Dinner:" << RET << " Rice 1.5 cups, Protein 150g, Vegetables 1 cup\n";
            cout << GT << "Snacks:" << RET << " Nuts 30g, Peanut butter 2 tbsp\n";
        }

        else if (ageGroup == "Adult")
        {
            cout << GT << "Breakfast:" << RET << " Milk 250 ml, Eggs 2, Oats 40g\n";
            cout << GT << "Lunch:" << RET << " Rice 1.5 cups, Chicken/Fish 150g, Vegetables 1.5 cups\n";
            cout << GT << "Dinner:" << RET << " Rice 1 cup, Protein 120g, Vegetables 1 cup\n";
            cout << GT << "Snacks:" << RET << " Nuts 25g, Fruit 1\n";
        }

        else // Senior
        {
            cout << GT << "Breakfast:" << RET << " Milk 200 ml, Soft egg 1-2, Banana 1\n";
            cout << GT << "Lunch:" << RET << " Rice 1 cup, Fish 100g, Vegetables 1.5 cups\n";
            cout << GT << "Dinner:" << RET << " Soft khichdi/Soup, Protein 80-100g\n";
            cout << GT << "Snacks:" << RET << " Nuts 15g, Fruit 1, Yogurt 100g\n";
        }
    }

    // ================= NORMAL =================
    else if (bmi >= 18.5 && bmi <= 24.9)
    {
        cout << YT << "Goal -------- Maintain Healthy Body" << RET << endl;

        if (ageGroup == "Teen")
        {
            cout << GT << "Breakfast:" << RET << " Milk 250 ml, Egg 1, Bread 1 slice, Fruit 1\n";
            cout << GT << "Lunch:" << RET << " Rice 1.5 cups, Fish/Chicken 100g, Vegetables 1 cup, Dal 0.5 cup\n";
            cout << GT << "Dinner:" << RET << " Rice 1 cup, Protein 100g, Vegetables 1 cup\n";
            cout << GT << "Snacks:" << RET << " Fruit 1, Biscuits 2\n";
        }

        else if (ageGroup == "Young Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 50g, Eggs 1-2, Milk 200 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 1.5 cups, Protein 120g, Vegetables 1-2 cups\n";
            cout << GT << "Dinner:" << RET << " 2 roti or Rice 1 cup, Protein 100g, Vegetables\n";
            cout << GT << "Snacks:" << RET << " Nuts 20g, Tea\n";
        }

        else if (ageGroup == "Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 40g, Egg 1, Milk 200 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 1-1.5 cups, Protein 120g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " 2 roti, Protein 100g, Vegetables 2 cups\n";
            cout << GT << "Snacks:" << RET << " Fruit 1, Nuts 20g\n";
        }

        else // Senior
        {
            cout << GT << "Breakfast:" << RET << " Milk 200 ml, Soft porridge 40g\n";
            cout << GT << "Lunch:" << RET << " Rice 1 cup, Fish 80g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " Soup + soft vegetables + Protein 80g\n";
            cout << GT << "Snacks:" << RET << " Fruit 1, Yogurt 100g\n";
        }
    }

    // ================= OVERWEIGHT =================
    else if (bmi >= 25 && bmi <= 29.9)
    {
        cout << YT << "Goal -------- Weight Loss" << RET << endl;

        if (ageGroup == "Teen")
        {
            cout << GT << "Breakfast:" << RET << " Egg 1, Bread 1 slice, Milk 200 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 1 cup, Protein 100g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " 2 roti, Protein 80g, Vegetables 2 cups\n";
            cout << GT << "Snacks:" << RET << " Fruit 1, Avoid junk food\n";
        }

        else if (ageGroup == "Young Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 40g, Egg 1, Green tea\n";
            cout << GT << "Lunch:" << RET << " Brown rice 1 cup, Chicken/Fish 120g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " Salad 2 cups, Protein 100g\n";
            cout << GT << "Snacks:" << RET << " Apple 1, Nuts 15g\n";
        }

        else if (ageGroup == "Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 40g, Egg 1\n";
            cout << GT << "Lunch:" << RET << " Rice 1 cup, Protein 120g, Vegetables 2-3 cups\n";
            cout << GT << "Dinner:" << RET << " Soup + Salad, Protein 100g\n";
            cout << GT << "Snacks:" << RET << " Roasted chickpeas 25g\n";
        }

        else // Senior
        {
            cout << GT << "Breakfast:" << RET << " Oats 30g, Milk 150 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 0.5-1 cup, Fish 80g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " Soup + soft vegetables\n";
            cout << GT << "Snacks:" << RET << " Fruit 1\n";
            cout << GT << "\nNote:" << RET << " Avoid strict dieting, focus on light activity.\n";
        }
    }

    // ================= OBESE =================
    else
    {
        cout << YT << "Goal -------- Obesity Management" << RET << endl;

        if (ageGroup == "Teen")
        {
            cout << GT << "Breakfast" << RET << ": Egg 1, Milk 200 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 1 cup, Protein 100g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " 2 roti, Vegetables 2 cups, Protein 80g\n";
            cout << GT << "Snacks:" << RET << " Fruits only\n";
        }

        else if (ageGroup == "Young Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 30g, Egg whites 2\n";
            cout << GT << "Lunch:" << RET << " Brown rice 0.5-1 cup, Protein 100g, Vegetables 2 cups\n";
            cout << GT << "Dinner:" << RET << " Salad + Soup, Protein 100g\n";
            cout << GT << "Snacks:" << RET << " Fruits, Green tea\n";
        }

        else if (ageGroup == "Adult")
        {
            cout << GT << "Breakfast:" << RET << " Oats 30g, Egg 1\n";
            cout << GT << "Lunch:" << RET << " Rice 0.5-1 cup, Protein 100g, Vegetables 3 cups\n";
            cout << GT << "Dinner:" << RET << " Soup + Salad, Protein 80-100g\n";
            cout << GT << "Snacks:" << RET << " Nuts 10g, Fruit\n";
        }

        else // Senior
        {
            cout << GT << "Breakfast:" << RET << " Soft oats 30g, Milk 150 ml\n";
            cout << GT << "Lunch:" << RET << " Rice 0.5 cup, Fish 80g, Vegetables 2-3 cups\n";
            cout << GT << "Dinner:" << RET << " Soup + soft vegetables\n";
            cout << GT << "Snacks:" << RET << " Fruit only\n";
            cout << GT << "\nSenior Note:" << RET << " Safe weight loss only, no fasting.\n";
        }
    }
    cout << GT << "Drink enough water(2.1-3.1 liters) and avoid excessive sugar and fried food and exercise regularly." << RET << endl;
}
int main()
{
    int choice;
Level_1:
    cout << YT << "\n------- MENU -------" << RET << endl;
    cout << "1. Register\n";
    cout << "2. Login\n";
    cout << "3. Exit\n";
    cout << GT << "Enter choice: " << RET;
    cin >> choice;
    switch (choice)
    {
    case 1:
        registerUser();
        goto Level_1;
    case 2:
    {
        string username;
        if (loginUser(username))
        {
            cout << GT << "-------Login successful!-------" << RET << endl;
            cout << endl;
            float bmi = 0, whtr = 0, ibws = 0, ibwe = 0, bodyfat = 0, weight = 0;
            string nutrition = "";
            bool diet = false;
        level_2:
            cout << "1. Health Assistant\n";
            cout << "2. Chatbot\n";
            cout << "3. Saved data\n";
            cout << "4. Diet Plan\n";
            cout << "5. Back to menu\n";
            cout << "6. Exit\n";

            int num;
            cout << YT << "Enter a number: " << RET;
            cin >> num;
        level_3:
            switch (num)
            {
            case 1:
            level_4:
                diet = true;
                float height, waist, muac;
                int age;
                char gender;

                cout << BT << "Enter weight (kg): " << RET;
                cin >> weight;

                cout << BT << "Enter height (cm): " << RET;
                cin >> height;

                cout << BT << "Enter waist circumference (cm): " << RET;
                cin >> waist;

                cout << BT << "Enter age: " << RET;
                cin >> age;

                cout << BT << "Enter gender (m/f): " << RET;
                cin >> gender;

                HealthIndices(weight, height, waist, age, gender, bmi, whtr, ibws, ibwe, bodyfat, nutrition);

                if (bmi >= 18.5 && bmi <= 24.9)
                    cout << "\nBMI (Body Mass Index): " << GT << fixed << setprecision(1) << bmi << RET << endl;
                else
                    cout << "\nBMI (Body Mass Index): " << RT << fixed << setprecision(1) << bmi << RET << endl;
                if (whtr < 0.5)
                    cout << "WHtR (Waist-to-Height Ratio): " << GT << fixed << setprecision(1) << whtr << RET << endl;
                else
                    cout << "WHtR (Waist-to-Height Ratio): " << RT << fixed << setprecision(1) << whtr << RET << endl;
                if (bodyfat > 25)
                    cout << "Body Fat: " << RT << fixed << setprecision(2) << bodyfat << " %" << RET << endl;
                else
                    cout << "Body Fat: " << GT << fixed << setprecision(2) << bodyfat << " %" << RET << endl;
                cout << "Ideal Body Weight: " << GT << fixed << setprecision(2) << ibws << RET << " to " << GT << fixed << setprecision(2) << ibwe << " kg" << RET << endl;
                cout << "Nutrition Status: " << nutrition << endl;
                saveData(username, age, bmi, whtr, ibws, ibwe, bodyfat, nutrition);
                healthAdvice(bmi, whtr, bodyfat, gender, age);
                weightAdjustment(weight, height, age, bmi);
                cout << YT << "Enter a number(5 for Menu): " << RET;
                cin >> num;
                goto level_3;
                break;
            case 2:
                chatbot(username);
                cout << YT << "Enter a number(5 for Menu): " << RET;
                cin >> num;
                goto level_3;
                break;
            case 3:
                showData(username);
                cout << YT << "Enter a number(5 for Menu): " << RET;
                cin >> num;
                goto level_3;
                break;
            case 4:
            {
                char count;

                if (!diet)
                {
                    cout << RT << "First use assistant!\n"
                         << RET;
                    cout << "Press" << YT << "'p'" << RET << "to use previous data or press" << YT << "'1'" << RET << "for assistant: ";
                    cout << YT;
                    cin >> count;
                    cout << RET;
                    if (count == '1')
                    {
                        goto level_4;
                    }
                    else if (count == 'p')
                    {
                        float oldBMI = getLastBMI(username);
                        int oldAge = getLastAge(username);
                        if (oldBMI == -1 || oldAge == -1)
                        {
                            cout << RT << "No previous data found!" << RET << endl;
                        }
                        else
                        {
                            cout << BT << "\nUsing previous BMI: " << fixed << setprecision(1) << oldBMI << RET << endl;
                            cout << BT << "Using previous Age:" << oldAge << RET << endl;
                            dietPlan(oldBMI, oldAge);
                        }
                    }
                    else
                    {
                        cout << RT << "Invalid choice!\n"
                             << RET;
                    }
                }
                else
                {
                    dietPlan(bmi, age);
                }
                cout << YT << "Enter a number(5 for Menu): " << RET;
                cin >> num;
                goto level_3;
                break;
            }
            case 5:
                cout << "1. Health Assistant\n";
                cout << "2. Chatbot\n";
                cout << "3. Saved data\n";
                cout << "4. Diet Plan\n";
                cout << "5. Back to menu\n";
                cout << "6. Exit\n";
                cout << YT << "Enter a number: " << RET;
                cin >> num;
                goto level_3;
                break;
            case 6:
                goto Level_1;
                break;
            default:
                cout << RT << "Enter valid number!" << RET << endl;
                goto level_2;
                break;
            }
        }
        else
        {
            cout << RT << "Invalid username or password!" << RET << endl;
            goto Level_1;
        }
        break;
    }
    case 3:
        cout << YT << "GOODBYE!" << RET;
        break;
    default:
        cout << RT << "Invalid choice!" << RET << endl;
        goto Level_1;
        break;
    }
    return 0;
}
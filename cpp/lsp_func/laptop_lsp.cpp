#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <string>

using namespace std;

// Evaluates preferred large values
double LARGE(double aa, double A, double B)
{
    return 100.0 * min(1.0, max(0.0, (aa - A) / (B - A)));
}

// Evaluates preferred small values
double SMALL(double aa, double C, double D)
{
    return 100.0 * min(1.0, max(0.0, (D - aa) / (D - C)));
}

// Evaluates preferred range of values
double RANGE(double aa, double A, double B, double C, double D)
{
    return 100.0 * min(1.0, max({0.0, (aa - A) / (B - A), (D - aa) / (D - C)}));
}

// Aggregates scores using Weighted Power Mean (WPM)
double GCD(const vector<double>& xx, const vector<double>& ww, double rr)
{
    double sum = 0.0;
    for (size_t ii = 0; ii < xx.size(); ++ii)
    {
        // Iterate through the arrays
        double normalized_x = xx[ii] / 100.0;
        sum += ww[ii] * pow(normalized_x, rr);
    }
    return 100.0 * pow(sum, 1.0 / rr);
}

int main()
{
    // Define cost thresholds
    double min_cost = 1200.0;
    double max_cost = 2500.0;

    // Loop to accept inputs for 3 computers at a time
    for (int ii = 0; ii < 3; ++ii) {
        string comp_name;
        double battery_life, screen_size, ssd_capacity, ram_amount;
        double cores_threads, weight_lbs, repairability_rating, warranty_time, total_cost;

        // --- Accept User Inputs ---
        cout << "\n--- Enter data for Computer " << (ii + 1) << " ---\n";
        cout << "Name: ";
        cin >> ws; // Clear leading whitespace
        getline(cin, comp_name);
        cout << "Battery Life (hours): "; cin >> battery_life;
        cout << "Screen Size (inches): "; cin >> screen_size;
        cout << "SSD Capacity (GB): "; cin >> ssd_capacity;
        cout << "RAM (GB): "; cin >> ram_amount;
        cout << "Cores-Threads: "; cin >> cores_threads;
        cout << "Weight (lbs): "; cin >> weight_lbs;
        cout << "Repairability (1-10): "; cin >> repairability_rating;
        cout << "Warranty (months): "; cin >> warranty_time;
        cout << "Total Cost ($): "; cin >> total_cost;

        // --- Calculate Attribute Suitability Scores ---
        double battery_score = LARGE(battery_life, 4.0, 10.0);
        double screen_score = RANGE(screen_size, 13.0, 14.0, 16.0, 18.0);
        double ssd_score = LARGE(ssd_capacity, 512.0, 2000.0);
        double ram_score = LARGE(ram_amount, 16.0, 32.0);
        double cores_score = LARGE(cores_threads, 8.0, 16.0);
        double weight_score = SMALL(weight_lbs, 3.0, 6.0);
        double repairability_score = LARGE(repairability_rating, 3.0, 8.0);
        double warranty_score = LARGE(warranty_time, 12.0, 36.0);

        // --- Logic Aggregation Branches ---
        // Performance Block (Simultaneity: rr = -1.0)
        vector<double> perf_xx = {ram_score, cores_score, ssd_score};
        vector<double> perf_ww = {0.4, 0.4, 0.2};
        double performance_score = GCD(perf_xx, perf_ww, -1.0);

        // Portability Block (Neutrality: rr = 1.0)
        vector<double> port_xx = {battery_score, screen_score, weight_score};
        vector<double> port_ww = {0.4, 0.4, 0.2};
        double portability_score = GCD(port_xx, port_ww, 1.0);

        // Reliability Block (Substitutability: rr = 2.0)
        vector<double> rel_xx = {repairability_score, warranty_score};
        vector<double> rel_ww = {0.6, 0.4};
        double reliability_score = GCD(rel_xx, rel_ww, 2.0);

        // --- Calculate Overall Suitability (X) ---
        // Top-Level Tree (Neutrality: rr = 1.0)
        vector<double> overall_xx = {performance_score, portability_score, reliability_score};
        vector<double> overall_ww = {0.5, 0.3, 0.2};
        double overall_suitability = GCD(overall_xx, overall_ww, 1.0);

        // --- Calculate Overall Value (V) ---
        // Applies conjunction logic using the affordability threshold
        double cost_factor = max(0.0, min(1.0, (max_cost - total_cost) / (max_cost - min_cost)));
        double overall_value = overall_suitability * cost_factor;

        // --- Output Results ---
        cout << "\nResults for " << comp_name << ":" << endl;
        cout << "Performance Score: " << performance_score << "%" << endl;
        cout << "Portability Score: " << portability_score << "%" << endl;
        cout << "Reliability Score: " << reliability_score << "%" << endl;
        cout << "Overall Suitability (X): " << overall_suitability << "%" << endl;
        cout << "Overall Value (V): " << overall_value << "%" << endl;
        cout << "--------------------------------\n";
    }
    return 0;
}

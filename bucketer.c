#include <stdio.h>
#include <assert.h>

// Define a struct to hold the counts for different battery health statuses.
struct CountsBySoH {
  int healthy;
  int exchange;
  int failed;
};

// Function to count batteries by their State of Health (SoH).
struct CountsBySoH countBatteriesByHealth(const int* presentCapacities, int nBatteries) {
  struct CountsBySoH counts = {0, 0, 0};
  int ratedCapacity = 120;  // The rated capacity for batteries.

  for (int i = 0; i < nBatteries; i++) {
    double soh = ((double)presentCapacities[i] / ratedCapacity) * 100;

    // Categorize batteries based on SoH percentages.
    if (soh >= 80 && soh <= 100) {
      counts.healthy++;
    } else if (soh >= 63 && soh < 80) {
      counts.exchange++;
    } else {
      counts.failed++;
    }
  }

  return counts;
}

// Test the countBatteriesByHealth function.
void testBucketingByHealth() {
  const int presentCapacities[] = {113, 116, 80, 95, 92, 70};
  const int numberOfBatteries = sizeof(presentCapacities) / sizeof(presentCapacities[0]);
  printf("Counting batteries by State of Health (SoH)...\n");

  // Obtain the counts for different health categories.
  struct CountsBySoH counts = countBatteriesByHealth(presentCapacities, numberOfBatteries);

  // Assert the results.
  assert(counts.healthy == 2);
  assert(counts.exchange == 3);
  assert(counts.failed == 1);

   // Test cases for boundary conditions and edge cases.
  const int perfectBattery[] = {120};  // A battery with 100% SoH
  const int zeroCapacityBattery[] = {0};  // A battery with 0% SoH
  const int emptyArray[] = {};  // An empty array
  const int allFailed[] = {60, 59, 50};  // All batteries with SoH < 63

  // Test for a perfect battery.
  counts = countBatteriesByHealth(perfectBattery, 1);
  assert(counts.healthy == 1);
  assert(counts.exchange == 0);
  assert(counts.failed == 0);

  // Test for a battery with 0% SoH.
  counts = countBatteriesByHealth(zeroCapacityBattery, 1);
  assert(counts.healthy == 0);
  assert(counts.exchange == 0);
  assert(counts.failed == 1);

  // Test with an empty array.
  counts = countBatteriesByHealth(emptyArray, 0);
  assert(counts.healthy == 0);
  assert(counts.exchange == 0);
  assert(counts.failed == 0);

  // Test with all batteries failing.
  counts = countBatteriesByHealth(allFailed, 3);
  assert(counts.healthy == 0);
  assert(counts.exchange == 0);
  assert(counts.failed == 3);

  printf("Done counting batteries by SoH :)\n");
}

int main() {
  // Run the test.
  testBucketingByHealth();
  return 0;
}

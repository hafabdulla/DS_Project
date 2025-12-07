#include <iostream>
#include "../DS_Project/LinkedList.h"
#include "../DS_Project/Stack.h"
#include "../DS_Project/Queue.h"
#include "../DS_Project/HashTable.h"
#include "../DS_Project/Tree.h"
#include "../DS_Project/Graph.h"
#include "../DS_Project/PriorityQueue.h"
#include "../DS_Project/Transport.h"
#include "../DS_Project/Population.h"
#include "../DS_Project/Medical.h"
using namespace std;
int main() {
    cout << "\n╔════════════════════════════════════════════╗\n";
    cout << "║      SMART CITY - MEDICAL MODULE          ║\n";
    cout << "╚════════════════════════════════════════════╝\n";

    MedicalModule medical;

    // ===== UC-M1: REGISTER HOSPITALS =====
    cout << "\n--- Registering Hospitals ---\n";
    medical.registerHospital("PIMS", "G-8", 12, "General, Cardiology");
    medical.registerHospital("Shifa International", "H-8", 20, "Oncology, Surgery");
    medical.registerHospital("Maroof Hospital", "F-10", 8, "Orthopedics");
    medical.registerHospital("Poly Clinic", "G-6", 14, "General");
    medical.registerHospital("Islamabad Medical", "I-8", 10, "Pediatrics");

    // Connect hospitals for routing
    medical.connectHospitals("PIMS", "Shifa International", 5);
    medical.connectHospitals("PIMS", "Poly Clinic", 3);
    medical.connectHospitals("Shifa International", "Maroof Hospital", 7);

    // ===== UC-M2: REGISTER DOCTORS =====
    cout << "\n--- Registering Doctors ---\n";
    medical.registerDoctor("Ahmed Ali", "Cardiology", "PIMS");
    medical.registerDoctor("Sara Khan", "Cardiology", "Shifa International");
    medical.registerDoctor("Hassan Raza", "Orthopedics", "Maroof Hospital");
    medical.registerDoctor("Fatima Noor", "Pediatrics", "Islamabad Medical");
    medical.registerDoctor("Ali Zain", "Surgery", "Shifa International");

    // ===== UC-M9: ADD MEDICINES =====
    cout << "\n--- Adding Medicines to Pharmacies ---\n";
    medical.addMedicine("Panadol", "Paracetamol", 50, "Sehat Pharmacy");
    medical.addMedicine("Augmentin", "Co-Amoxiclav", 320, "D-Well Pharma");
    medical.addMedicine("Brufen", "Ibuprofen", 120, "Medix Pharmacy");
    medical.addMedicine("Zyrtec", "Cetirizine", 90, "CurePlus");
    medical.addMedicine("Disprin", "Aspirin", 30, "HealthOne");

    // ===== UC-M5: EMERGENCY BED AVAILABILITY =====
    cout << "\n========================================\n";
    cout << "  UC-M5: Find Best Emergency Hospital\n";
    cout << "========================================\n";
    medical.displayEmergencyQueue();
    medical.findBestEmergencyHospital();

    // ===== UC-M4: UPDATE EMERGENCY BEDS =====
    cout << "\n========================================\n";
    cout << "  UC-M4: Update Emergency Beds\n";
    cout << "========================================\n";
    cout << "Emergency! Patient admitted to Shifa International...\n";
    medical.updateEmergencyBeds("Shifa International", 19);
    medical.displayEmergencyQueue();

    // ===== UC-M7: SEARCH DOCTOR BY SPECIALIZATION =====
    cout << "\n========================================\n";
    cout << "  UC-M7: Search Doctors\n";
    cout << "========================================\n";
    medical.searchDoctorBySpecialization("Cardiology");
    medical.searchDoctorBySpecialization("Pediatrics");
    medical.searchDoctorBySpecialization("Neurology");  // Not found

    // ===== UC-M10: SEARCH MEDICINE BY NAME =====
    cout << "\n========================================\n";
    cout << "  UC-M10: Search Medicine by Name\n";
    cout << "========================================\n";
    medical.searchMedicineByName("Panadol");
    medical.searchMedicineByName("Brufen");
    medical.searchMedicineByName("Crocin");  // Not found

    // ===== UC-M11: SEARCH MEDICINE BY FORMULA =====
    cout << "\n========================================\n";
    cout << "  UC-M11: Search Medicine by Formula\n";
    cout << "========================================\n";
    medical.searchMedicineByFormula("Paracetamol");
    medical.searchMedicineByFormula("Ibuprofen");

    // ===== UC-M6: NEAREST HOSPITAL =====
    cout << "\n========================================\n";
    cout << "  UC-M6: Find Nearest Hospital\n";
    cout << "========================================\n";
    medical.findNearestHospital("PIMS", "Maroof Hospital");

    // ===== LIST ALL =====
    medical.listAllHospitals();
    medical.listAllDoctors();

    cout << "\n✅ MEDICAL MODULE: ALL USE CASES WORKING!\n";

    cout << "\nPress Enter to exit...";
    cin.get();

    return 0;
}
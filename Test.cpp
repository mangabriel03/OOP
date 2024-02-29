
#include "Controller.h"
#include "Repository.h"
#include "Test.h"
#include <assert.h>


/**
 teste pentru toate functiile din Repository
 */
void testAddRepo() {
    InMemoryRepository repository;
    //adauga un obiect
    repository.addRepo(ElectricScooter{ "1", "m1", 1000,"avram","parked",{1,1,2023}});
    assert(repository.getAll().size() == 1);
    assert(repository.findElectricScooter("1").getModel() == "m1");
    assert(repository.findElectricScooter("1").getKilometers() == 1000);
    assert(repository.findElectricScooter("1").getLastLocation() == "avram");
    assert(repository.findElectricScooter("1").getCurrentState() == "parked");
    assert(repository.findElectricScooter("1").getCommissioningDate().day == 1);
    assert(repository.findElectricScooter("1").getCommissioningDate().month == 1);
    assert(repository.findElectricScooter("1").getCommissioningDate().year == 2023);
    //adauga al doilea obiect
    repository.addRepo(ElectricScooter{ "2", "m2", -1,"avram","parked",{11,11,2021}});
    //lungimea listei este 2
    assert(repository.getAll().size() == 2);

    //cauta obiect cu id inexistent
    try {
        repository.findElectricScooter("8");
        assert(false);
    }
    catch (RepoException&) {
        assert(true);
    }

    //obiectul cu id=1, este pe pozitia 0 in lista
    assert(repository.find("1") == 0);
}

void testDeleteRepo() {
    InMemoryRepository repository;
    repository.addRepo(ElectricScooter{ "1", "m1", 1000,"avram","parked",{1,1,2023}});
    repository.addRepo(ElectricScooter{ "2", "m2", 2000,"cipariu","parked",{11,11,2021}});
    assert(repository.getAll().size() == 2);
    ElectricScooter electricScooter={"3", "m3", 1500,"avram","parked",{5,6,2020}};
    repository.addRepo(electricScooter);
    assert(repository.getAll().size() == 3);
    repository.deleteRepo(electricScooter);
    assert(repository.getAll().size() == 2);
}

void testUpdateRepo() {
    InMemoryRepository repository;
    repository.addRepo(ElectricScooter{ "1", "m1", 1000,"avram","parked",{1,1,2023}});
    repository.addRepo(ElectricScooter{ "2", "m2", 2000,"cipariu","parked",{11,11,2021}});
    assert(repository.getAll().size() == 2);
    ElectricScooter electricScooter={"1", "m3", 1500,"avram","reserved",{5,6,2020}};
    repository.updateRepo(electricScooter);
    assert(repository.findElectricScooter("1").getModel() == "m3");
    assert(repository.findElectricScooter("1").getKilometers() == 1500);
    assert(repository.findElectricScooter("1").getLastLocation() == "avram");
    assert(repository.findElectricScooter("1").getCurrentState() == "reserved");
    assert(repository.findElectricScooter("1").getCommissioningDate().day == 5);
    assert(repository.findElectricScooter("1").getCommissioningDate().month == 6);
    assert(repository.findElectricScooter("1").getCommissioningDate().year == 2020);
    assert(repository.getAll().size() == 2);
}

void testReserveRepo(){
    InMemoryRepository repository;
    repository.addRepo(ElectricScooter{ "1", "m1", 1000,"avram","parked",{1,1,2023}});
    repository.reserveRepo("1");
    assert(repository.findElectricScooter("1").getCurrentState() == "reserved");
}

void testUseRepo(){
    InMemoryRepository repository;
    repository.addRepo(ElectricScooter{ "1", "m1", 1000,"avram","parked",{1,1,2023}});
    repository.useRepo("1");
    assert(repository.findElectricScooter("1").getCurrentState() == "in use");
}

void Test::testeRepo() {
    testAddRepo();
    testDeleteRepo();
    testUpdateRepo();
    testReserveRepo();
    testUseRepo();
}


/**
 teste pentru toate functiile din Controller
 */
void testAddController() {
    InMemoryRepository repository;
    Validator validator;
    Controller controller{ repository,validator };
    controller.addController("1", "m1", 1000,"avram","parked",{1,1,2023});
    assert(controller.getAll().size() == 1);

    //add something invalid
    try {
        controller.addController("1", "m1", -10000,"cipariu","parked",{-1,4,202});
        assert(false);
    }
    catch (ValidateException&) {
        assert(true);
    }
    //add a electricScooter that exists
    //controller.addController("1", "m1", 1000,"avram","parked",{1,1,2023});
    assert(controller.getAll().size() == 1);
}

void testFilter() {
    InMemoryRepository repository;
    Validator validator;
    Controller controller{ repository,validator };
    controller.addController("1", "m1", 1000,"avram","parked",{1,1,2023});
    controller.addController("2", "m2", 7000, "matei","reserved", {11,1,2020});
    controller.addController("3", "m3", 3000, "avram","in use", {12,3,2022});
    controller.addController("4", "m4", 9000, "cipariu","parked", {1,12,2020});
    controller.addController("5", "m5", 10000, "avram","reserved", {11,8,2021});
    controller.addController("6", "m6", 30000, "cipariu","parked", {22,7,2022});
    assert(controller.filterByLocation("avram").size() == 3);
    assert(controller.filterByLocation("matei").size() == 1);
    assert(controller.filterByLocation("cipariu").size() == 2);
    assert(controller.filterByLocationAndCurrentState("avram").size() == 1);
}

void testSort() {
    InMemoryRepository repository;
    Validator validator;
    Controller controller{ repository,validator };
    controller.addController("1", "m1", 1000,"avram","parked",{1,1,2023});
    controller.addController("2", "m2", 7000, "matei","reserved", {11,1,2020});
    controller.addController("3", "m3", 3000, "avram","in use", {12,3,2022});
    controller.addController("4", "m4", 9000, "cipariu","parked", {1,12,2020});
    controller.addController("5", "m5", 10000, "avram","reserved", {11,8,2021});
    controller.addController("6", "m6", 30000, "cipariu","parked", {22,7,2022});
    auto firstElectricScooter = controller.sortByCommissioningDate()[0];
    assert(firstElectricScooter.getId() == "2");
}

void Test::testController() {
    testAddController();
    testFilter();
    testSort();
}

void Test::testAll() {
    testeRepo();
    testController();
}


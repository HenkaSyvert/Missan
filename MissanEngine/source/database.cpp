#include "util/database.hpp"


using namespace Missan;



void Database::Copy(size_t destinationId, size_t sourceId) {
	for (auto& table : tables) if (table->Get(sourceId)) table->Add(destinationId, table->Get(sourceId));	
}

void Database::RemoveAll(size_t id) {
	for (auto* table : tables) table->Remove(id);
}
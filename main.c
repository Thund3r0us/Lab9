// Nicole Walsh, Spring 2024

#include <stdio.h>
#include <stdlib.h>

// RecordType
struct RecordType
{
	int		id;
	char	name;
	int		order; 
};

// Fill out this structure (size of 23)
struct HashType
{
  struct Node* array[23];
};

// Node for chaining
struct Node
{
  struct RecordType data;
  struct Node* next;
};

// Compute the hash function 
int hash(int x)
{
  return x % 23; // Modulo division to fit within array size
};

// parses input file to an integer array
int parseData(char* inputFileName, struct RecordType** ppData)
{
	FILE* inFile = fopen(inputFileName, "r");
	int dataSz = 0;
	int i, n;
	char c;
	struct RecordType *pRecord;
	*ppData = NULL;

	if (inFile)
	{
		fscanf(inFile, "%d\n", &dataSz);
		*ppData = (struct RecordType*) malloc(sizeof(struct RecordType) * dataSz);
		// Implement parse data block
		if (*ppData == NULL)
		{
			printf("Cannot allocate memory\n");
			exit(-1);
		}
		for (i = 0; i < dataSz; ++i)
		{
			pRecord = *ppData + i;
			fscanf(inFile, "%d ", &n);
			pRecord->id = n;
			fscanf(inFile, "%c ", &c);
			pRecord->name = c;
			fscanf(inFile, "%d ", &n);
			pRecord->order = n;
		}

		fclose(inFile);
	}

	return dataSz;
}

// prints the records
void printRecords(struct RecordType pData[], int dataSz)
{
	int i;
	printf("\nRecords:\n");
	for (i = 0; i < dataSz; ++i)
	{
		printf("\t%d %c %d\n", pData[i].id, pData[i].name, pData[i].order);
	}
	printf("\n\n");
}

// display records in the hash structure
// skip the indices which are free
// the output will be in the format:
// index x -> id, name, order -> id, name, order ....
void displayRecordsInHash(struct HashType *pHashArray, int hashSz)
{
	for (int i = 0; i < hashSz; i++)  {
    printf("Index %d -> ", i);
    struct Node* current = pHashArray->array[i];
    while (current != NULL) {
      printf("%d %c %d -> ", current->data.id, current->data.name, current->data.order);
      current = current->next;
    }
    printf("NULL\n");
	}
}

// main function
int main(void)
{
	struct RecordType *pRecords;
	int recordSz = 0;

	recordSz = parseData("input.txt", &pRecords);
	printRecords(pRecords, recordSz);
	
  // Your hash implementation

  // Hash table creation
  struct HashType hashArray;
  int size = 23;

  // Initialize hash table
  for (int i = 0; i < 23; ++i) {
    hashArray.array[i] = NULL;
  }

  // Populate hash table
  for (int i = 0; i < recordSz; ++i) {
    int index = hash(pRecords[i].id);
    struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
    if (newNode == NULL) {
      fprintf(stderr, "Memory allocation failed\n");
      exit(EXIT_FAILURE);
    }
    newNode->data = pRecords[i];
    newNode->next = hashArray.array[index];
    hashArray.array[index] = newNode;
  }

  // Display records in the hash structure
  displayRecordsInHash(&hashArray, size);

  // Free allocated memory
  for (int i = 0; i < 23; ++i) {
    struct Node* current = hashArray.array[i];
    while (current != NULL) {
      struct Node* temp = current;
      current = current->next;
      free(temp);
    }
  }

  free(pRecords);

  return 0;
}

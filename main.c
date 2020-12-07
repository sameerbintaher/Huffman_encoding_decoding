// C program for Huffman Coding
#include<stdio.h>
#include<stdlib.h>
#define MAX_TREE_HT 100

// A Huffman tree node
struct MinHeapNode {

        // One of the input characters
        char data;

        // Frequency of the character
        unsigned freq;

        // Left and right child of this node
        struct MinHeapNode *left, *right;
};

// A Min Heap: Collection of
// min-heap (or Huffman tree) nodes
struct MinHeap {

        // Current size of min heap
        unsigned size;

        // capacity of min heap
        unsigned capacity;

        // Array of minheap node pointers
        struct MinHeapNode** array;
};

// A utility function allocate a new
// min heap node with given character
// and frequency of the character
struct MinHeapNode* newNode(char data, unsigned freq)
{
        struct MinHeapNode* temp
                = (struct MinHeapNode*)malloc
(sizeof(struct MinHeapNode));

        temp->left = temp->right = NULL;
        temp->data = data;
        temp->freq = freq;

        return temp;
}

// A utility function to create
// a min heap of given capacity
struct MinHeap* createMinHeap(unsigned capacity)

{

        struct MinHeap* minHeap
                = (struct MinHeap*)malloc(sizeof(struct MinHeap));

        // current size is 0
        minHeap->size = 0;

        minHeap->capacity = capacity;

        minHeap->array
                = (struct MinHeapNode**)malloc(minHeap->
capacity * sizeof(struct MinHeapNode*));
        return minHeap;
}

// A utility function to
// swap two min heap nodes
void swapMinHeapNode(struct MinHeapNode** a,
                                        struct MinHeapNode** b)

{

        struct MinHeapNode* t = *a;
        *a = *b;
        *b = t;
}

// The standard minHeapify function.
void minHeapify(struct MinHeap* minHeap, int idx)

{

        int smallest = idx;
        int left = 2 * idx + 1;
        int right = 2 * idx + 2;

        if (left < minHeap->size && minHeap->array[left]->
freq < minHeap->array[smallest]->freq)
                smallest = left;

        if (right < minHeap->size && minHeap->array[right]->
freq < minHeap->array[smallest]->freq)
                smallest = right;

        if (smallest != idx) {
                swapMinHeapNode(&minHeap->array[smallest],
                                                &minHeap->array[idx]);
                minHeapify(minHeap, smallest);
        }
}

// A utility function to check
// if size of heap is 1 or not
int isSizeOne(struct MinHeap* minHeap)
{

        return (minHeap->size == 1);
}

// A standard function to extract
// minimum value node from heap
struct MinHeapNode* extractMin(struct MinHeap* minHeap)

{

        struct MinHeapNode* temp = minHeap->array[0];
        minHeap->array[0]
                = minHeap->array[minHeap->size - 1];

        --minHeap->size;
        minHeapify(minHeap, 0);

        return temp;
}

// A utility function to insert
// a new node to Min Heap
void insertMinHeap(struct MinHeap* minHeap,
                                struct MinHeapNode* minHeapNode)

{

        ++minHeap->size;
        int i = minHeap->size - 1;

        while (i && minHeapNode->freq < minHeap->array[(i - 1) / 2]->freq) {

                minHeap->array[i] = minHeap->array[(i - 1) / 2];
                i = (i - 1) / 2;
        }

        minHeap->array[i] = minHeapNode;
}

// A standard function to build min heap
void buildMinHeap(struct MinHeap* minHeap)

{

        int n = minHeap->size - 1;
        int i;

        for (i = (n - 1) / 2; i >= 0; --i)
                minHeapify(minHeap, i);
}

// A utility function to print an array of size n
void printArr(int arr[], int n)
{
        int i;
        for (i = 0; i < n; ++i)
                printf("%d", arr[i]);

        printf("\n");
}

// Utility function to check if this node is leaf
int isLeaf(struct MinHeapNode* root)

{

        return !(root->left) && !(root->right);
}

// Creates a min heap of capacity
// equal to size and inserts all character of
// data[] in min heap. Initially size of
// min heap is equal to capacity
struct MinHeap* createAndBuildMinHeap(char data[], int freq[], int size)

{

        struct MinHeap* minHeap = createMinHeap(size);

        for (int i = 0; i < size; ++i)
                minHeap->array[i] = newNode(data[i], freq[i]);

        minHeap->size = size;
        buildMinHeap(minHeap);

        return minHeap;
}

// The main function that builds Huffman tree
struct MinHeapNode* buildHuffmanTree(char data[], int freq[], int size)

{
        struct MinHeapNode *left, *right, *top;

        // Step 1: Create a min heap of capacity
        // equal to size. Initially, there are
        // modes equal to size.
        struct MinHeap* minHeap = createAndBuildMinHeap(data, freq, size);

        // Iterate while size of heap doesn't become 1
        while (!isSizeOne(minHeap)) {

                // Step 2: Extract the two minimum
                // freq items from min heap
                left = extractMin(minHeap);
                right = extractMin(minHeap);

                // Step 3: Create a new internal
                // node with frequency equal to the
                // sum of the two nodes frequencies.
                // Make the two extracted node as
                // left and right children of this new node.
                // Add this node to the min heap
                // '$' is a special value for internal nodes, not used
                top = newNode('$', left->freq + right->freq);

                top->left = left;
                top->right = right;

                insertMinHeap(minHeap, top);
        }

        // Step 4: The remaining node is the
        // root node and the tree is complete.
        return extractMin(minHeap);
}

// Prints huffman codes from the root of Huffman Tree.
// It uses arr[] to store codes
void printCodes(struct MinHeapNode* root, int arr[], int top)
{


        // Assign 0 to left edge and recur
        if (root->left) {

                arr[top] = 0;
                printCodes(root->left, arr, top + 1);
        }

        // Assign 1 to right edge and recur
        if (root->right) {

                arr[top] = 1;
                printCodes(root->right, arr, top + 1);
        }

        // If this is a leaf node, then
        // it contains one of the input
        // characters, print the character
        // and its code from arr[]
        if (isLeaf(root)) {

                printf("%c: ", root->data);
                printArr(arr, top);
        }
}

void decode_(struct MinHeapNode* root, char s[])
{
    char ans[1000];
    int k = 0;
    struct MinHeapNode* curr = root;
    for (int i=0;i<strlen(s);i++)
    {
        if (s[i] == '0')
           curr = curr->left;
        else
           curr = curr->right;

        // reached leaf node
        if (curr->left==NULL && curr->right==NULL)
        {
            ans[k] = curr->data;
            k++;
            curr = root;
        }
    }
    // cout<<ans<<endl;
    printf("\nOutput the Huffman coding as follows: \n");
    printf("%s\n",ans);
}


// Driver program to test above functions
int main()
{

    int arr[MAX_TREE_HT], top = 0;

        char carr[100];
        int freq[100];

        struct MinHeapNode* root;

        int size;

        while(1){
        printf("\nPlease choose the function by input 1-4");
        printf("\n 1. Build the Huffman tree");
        printf("\n 2. Encode");
        printf("\n 3. Decode");
        printf("\n 4. Exit \n");
        int c;
        scanf("%d",&c);

        if(c==1){
            printf("\n Now the Huffman tree is building");
            printf("\nHow Many element would you like to use: ");
            scanf("%d",&size);
            for(int i=0;i<size;i++)
            {
                printf("\nPlease input the element %d: ",i+1);
                scanf(" %c",&carr[i]);
                printf("\nPlease input the weight of element %d: ",i+1);
                scanf("%d",&freq[i]);
            }
            root = buildHuffmanTree(carr, freq, size);
            printf("\nGreat the Huffman tree has been built\n");
        }
        else if(c==2){
            printf("Output of Huffman Coding \n");
            printCodes(root, arr, top);
        }
        else if(c==3){
            printf("Please input the message (0 or 1),ending with #: ");
            char p[100];
            scanf("%s",&p);
            decode_(root, p);
        }
        else if(c==4)
        break;

        }

    printf("Bye Bye. You're exiting from this world. Thank You Laoshi for this knowledge. I am Sameer.. Zaijian");

        return 0;
}

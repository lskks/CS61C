.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================

# int argmax(int* arr, int size)
# {
#     int max = arr[0];
#     int i = 1, pos = 0;

#     while (i < size)
#     {
#         if (max < arr[i])
#         {
#             pos = i;
#             max = arr[i];
#         }
#         i++;
#     }
# }
# =================================================================

argmax:
    # Prologue
    addi t0, x0, 1
    bge a1, t0, loop_start 
    li a0, 36 
    j exit

loop_start:
    lw t0, 0(a0)   # t0 = max
    li t1, 1       # i = t1
    li t2, 0       # pos = 0

loop_continue:
    bge t1, a1, loop_end

    slli t3, t1, 2
    add t4, a0, t3
    lw t5, 0(t4)    # t5 = arr[i]

    bge t0, t5, next # if max > arr[i], jump to next
    mv t2, t1
    mv t0, t5

next:
    addi t1, t1, 1
    j loop_continue

loop_end:
    # Epilogue
    mv  a0, t2
    jr ra

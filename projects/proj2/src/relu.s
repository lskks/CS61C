.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
# void relu(int* arr, int size)
# {
#     int i = 0;
#     while (i < size)
#     {
#         if (arr[i] < 0)
#             arr[i] = 0;
#         i++;
#     }
# }

relu:
    addi t0, x0, 1
    bge a1, t0, loop_start
    li a0, 36
    j exit

loop_start:
    li t0, 0
    
loop_continue:
    bge t0, a1, loop_end
    slli t1, t0, 2
    add t2, a0, t1
    lw t3, 0(t2)

    bge t3, x0, next
    sw x0, 0(t2)

next:
    addi t0, t0, 1
    j loop_continue

loop_end:
    # Epilogue
    jr ra


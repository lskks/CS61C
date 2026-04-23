.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================

# int dot(int* a0, int* a1, int a2, int a3, int a4)
# {
#     if (a2 < 1)
#         return 36;
#     if (a3 < 1 || a4 < 1)
#         return 37;
#
#     int sum = 0, product = 0;
#
#     for (int i = 0, j = 0, k = 0;i < a2;j += a3, k += a4, i++)
#     {
#         product = a0[j] * a1[k];
#         sum += product;
#     }
#     return sum;
# }

# =======================================================
dot:
    # Prologue
    addi t0, x0, 1
    blt a2, t0, number
    blt a3, t0, stride
    blt a4, t0, stride
    j loop_start

number:
    li a0, 36
    j exit

stride:
    li a0, 37
    j exit

loop_start:
    li t0, 0  # t0 = sum
    li t1, 0  # t1 = product
    li t2, 0  # t2 = i
    li t3, 0  # t3 = j
    li t4, 0  # t4 = k

loop_continue:

    slli t5, t3, 2
    slli t6, t4, 2

    add a5, t5, a0
    add a6, t6, a1

    lw a5, 0(a5)
    lw a6, 0(a6)

    mul t1, a5, a6
    add t0, t0, t1

    addi t2, t2, 1
    add t3, t3, a3
    add t4, t4, a4

    blt t2, a2, loop_continue

loop_end:


    # Epilogue
    mv a0, t0

    jr ra

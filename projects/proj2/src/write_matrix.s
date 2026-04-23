.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
# void write_matrix(char* filename, int* matrix, int row, int col)
# {
#     int fd = open(filename, O_WRONLY);
#     if (fd == -1)
#       exit(27);
#
#     int* r = &row;
#     int* c = &col;
#     if (write(fd, r, 4, 1) != 4)
#       exit(30);
#     if (write(fd, c, 4, 1) != 4);
#       exit(30);
#
#     if (write(fd, matrix, row * col, 4) != row * col)
#       exit(30) ;
#
#     if (close(fd) != 0)
#       exit(28);
# }
# ==============================================================================

write_matrix:

    # Prologue
    addi sp, sp, -32
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)
    sw s4, 20(sp)
    sw a2, 24(sp)
    sw a3, 28(sp)

    mv s1, a1
    mv s2, a2
    mv s3, a3

    # open the file
    li a1, 1
    jal ra, fopen
    li t0, -1
    beq a0, t0, fopen_failed
    mv s0, a0 # fd = a0

    # write the row
    addi a1, sp, 24
    li a2, 4
    li a3, 1
    jal ra, fwrite
    li t0, 4
    bne a0, t0, fwrite_failed
    
    # write the column
    mv a0, s0
    addi a1, sp, 28
    li a2, 4
    li a3, 1
    jal ra, fwrite
    li t0, 4
    bne a0, t0, fwrite_failed

    # write the matrix
    mv a0, s0
    mv a1, s1
    mul s4, s2, s3
    mv a2, s4
    li a3, 4
    jal ra, fwrite
    bne a0, s4, fwrite_failed

    # close the file
    mv a0, s0
    jal ra, fclose
    bne a0, x0, fclose_failed
    
    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw a2, 24(sp)
    lw a3, 28(sp)
    addi sp, sp, 32

    jr ra

fopen_failed:
    li a0, 27
    j exit

fwrite_failed:
    li a0, 30
    j exit

fclose_failed:
    li a0, 28
    j exit
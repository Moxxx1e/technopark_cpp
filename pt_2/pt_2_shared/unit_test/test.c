#include "gtest/gtest.h"

#include "../include/count.h"
#include "../include/read.h"

Comment_shared* create_array(unsigned int size)
{
    Comment_shared* array = (Comment_shared*)malloc(sizeof(Comment_shared) * size);
    return array;
}

double get_rand_mark()
{
    double value = rand() % 41 + 10;
    value /= 10;
    return value;
}

#define ID_MAX 100
#define MAX_VOICES 100
Comment_shared generate_random_comment()
{
    Comment_shared node;
    node.id = rand() % ID_MAX;
    node.mark = get_rand_mark();
    node.voices = rand() % MAX_VOICES + 1;
    return node;
}

Comment_shared generate_zero_comment()
{
    Comment_shared comment;
    comment.id = rand() % ID_MAX;
    comment.mark = 0;
    comment.voices = 0;
    return comment;
}

void fill_array(Comment_shared* array, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        Comment_shared new_comment = generate_random_comment();
        array[i] = new_comment;
    }
}

void fill_array_zeros(Comment_shared* array, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        Comment_shared zero_comment = generate_zero_comment();
        array[i] = zero_comment;
    }
}

int fill_array_dif_values(Comment_shared* array, unsigned int size)
{
    int zero_comments_counter = 0;
    for (int i = 0; i < size; i++) {
        int flag = rand() % 2;
        if (flag)
            array[i] = generate_random_comment();
        else {
            array[i] = generate_zero_comment();
            zero_comments_counter++;
        }
    }
    return zero_comments_counter;
}

TEST(count_novoices_comments_sh, null_array)
{
    Comment_shared* comments = NULL;
    unsigned int size = 2;
    EXPECT_EQ(count_novoices_comments_sh(comments, size), NULL_ARRAY_ERROR);
}

TEST(count_novoices_comments_sh, negative_size)
{
    int create_size = 5;
    Comment_shared* comments = create_array(create_size);
    if (!comments)
        return;
    fill_array(comments, create_size);

    int size = -2;
    EXPECT_EQ(count_novoices_comments_sh(comments, size), INVALID_SIZE_ERROR);
    free(comments);
}

TEST(count_novoices_comments_sh, zero_size)
{
    int create_size = 5;
    Comment_shared* comments = create_array(create_size);
    if (!comments)
        return;
    fill_array(comments, create_size);

    int size = 0;
    EXPECT_EQ(count_novoices_comments_sh(comments, size), INVALID_SIZE_ERROR);
    free(comments);
}

TEST(count_novoices_comments_sh, correct_array)
{
    int size = 2;
    Comment_shared* comments = create_array(size);
    comments[0] = { 0, 0, 0 };
    comments[1] = { 5, 1, 3.5 };
    EXPECT_EQ(count_novoices_comments_sh(comments, size), 1);
    free(comments);
}

TEST(count_novoices_comments_sh, zero_bad_voices)
{
    int size = 100;
    Comment_shared* comments = create_array(size);
    fill_array(comments, size);
    EXPECT_EQ(count_novoices_comments_sh(comments, size), 0);
    free(comments);
}

TEST(count_novoices_comments_sh, only_bad_voices)
{
    int size = 100;
    Comment_shared* comments = create_array(size);
    fill_array_zeros(comments, size);
    EXPECT_EQ(count_novoices_comments_sh(comments, size), size);
    free(comments);
}

TEST(count_novoices_comments_sh, ten_million_voices)
{
    int size = 10000000;
    Comment_shared* comments = create_array(size);
    if (!comments)
        return;
    int result = fill_array_dif_values(comments, size);
    EXPECT_EQ(count_novoices_comments_sh(comments, size), result);
    free(comments);
}

TEST(read_array_from_file_sh, not_existing_file)
{
    Comment_shared* comments = NULL;
    int size = 0;
    const char* filename = "../../test_files/not_existing_file.txt";
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), FILE_OPEN_ERROR);
}

TEST(read_array_from_file_sh, empty_file)
{
    const char* filename = "../../test_files/empty_file.txt";
    int size = 0;
    Comment_shared* comments = NULL;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), EMPTY_FILE_ERROR);
}

TEST(read_array_from_file_sh, number_of_comments_not_int)
{
    const char* filename = "../../test_files/fscanf_number_of_comments.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), FSCANF_NUMBER_OF_COMMENTS_ERROR);
    free(comments);
}

TEST(read_array_from_file_sh, invalid_voices)
{
    const char* filename = "../../test_files/invalid_voices.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), INVALID_VOICES_ERROR);
}

TEST(read_array_from_file_sh, invalid_mark)
{
    const char* filename = "../../test_files/invalid_mark.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), INVALID_MARK_ERROR);
}

TEST(read_array_from_file_sh, big_file)
{
    const char* filename = "../../test_files/one_million_nodes.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), SUCCESS);
    free(comments);
}

TEST(read_array_from_file_sh, cant_read_mark)
{
    const char* filename = "../../test_files/fscanf_mark.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), FSCANF_MARK_ERROR);
}

TEST(read_array_from_file_sh, cant_read_voices)
{
    const char* filename = "../../test_files/fscanf_voices.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), FSCANF_VOICES_ERROR);
}

TEST(read_array_from_file_sh, cant_read_id)
{
    const char* filename = "../../test_files/fscanf_id.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), FSCANF_ID_ERROR);
}

TEST(read_array_from_file_sh, invalid_number_of_comments)
{
    const char* filename = "../../test_files/not_positive_number_of_comments.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR);
}

// Number of comments is more than actual number of comments in file
TEST(read_array_from_file_sh, incorrect_number_of_comments)
{
    const char* filename = "../../test_files/incorrect_number_of_comments.txt";
    Comment_shared* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments, &size), INCORRECT_NUMBER_OF_COMMENTS_ERROR);
}

TEST(read_array_from_file_sh, correct_file)
{
    const char* filename = "../../test_files/correct_file.txt";
    Comment_shared* comments_in_file = NULL;
    Comment_shared comments[4] = {
            {0, 0, 0}, {5, 1, 2.3}, {521, 2, 4.5}, {10, 3, 3.3}
    };

    int size = 0;
    EXPECT_EQ(read_array_from_file_sh(filename, &comments_in_file, &size), SUCCESS);
    EXPECT_EQ(size, 4);
    for (int i = 0; i < size; i++) {
        EXPECT_EQ(comments[i].id, comments_in_file[i].id);
        EXPECT_EQ(comments[i].voices, comments_in_file[i].voices);
        EXPECT_EQ(comments[i].mark*10, comments_in_file[i].mark*10);
    }
    free(comments_in_file);
}

int main(int argc, char** argv)
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

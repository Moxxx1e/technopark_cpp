#include "gtest/gtest.h"

#include "../include/count.h"
#include "../include/read.h"

Comment_static* create_array(unsigned int size)
{
    Comment_static* array = (Comment_static*)malloc(sizeof(Comment_static) * size);
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
Comment_static generate_random_comment()
{
    Comment_static node;
    node.id = rand() % ID_MAX;
    node.mark = get_rand_mark();
    node.voices = rand() % MAX_VOICES + 1;
    return node;
}

Comment_static generate_zero_comment()
{
    Comment_static comment;
    comment.id = rand() % ID_MAX;
    comment.mark = 0;
    comment.voices = 0;
    return comment;
}

void fill_array(Comment_static* array, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        Comment_static new_comment = generate_random_comment();
        array[i] = new_comment;
    }
}

void fill_array_zeros(Comment_static* array, unsigned int size)
{
    for (int i = 0; i < size; i++) {
        Comment_static zero_comment = generate_zero_comment();
        array[i] = zero_comment;
    }
}

int fill_array_dif_values(Comment_static* array, unsigned int size)
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

TEST(count_novoices_comments_st, null_array)
{
    Comment_static* comments = NULL;
    unsigned int size = 2;
    EXPECT_EQ(count_novoices_comments_st(comments, size), NULL_ARRAY_ERROR);
}

TEST(count_novoices_comments_st, negative_size)
{
    int create_size = 5;
    Comment_static* comments = create_array(create_size);
    if (!comments)
        return;
    fill_array(comments, create_size);

    int size = -2;
    EXPECT_EQ(count_novoices_comments_st(comments, size), INVALID_SIZE_ERROR);
    free(comments);
}

TEST(count_novoices_comments_st, zero_size)
{
    int create_size = 5;
    Comment_static* comments = create_array(create_size);
    if (!comments)
        return;
    fill_array(comments, create_size);

    int size = 0;
    EXPECT_EQ(count_novoices_comments_st(comments, size), INVALID_SIZE_ERROR);
    free(comments);
}

TEST(count_novoices_comments_st, correct_array)
{
    int size = 2;
    Comment_static* comments = create_array(size);
    comments[0] = { 0, 0, 0 };
    comments[1] = { 1, 3.5, 5 };
    EXPECT_EQ(count_novoices_comments_st(comments, size), 1);
    free(comments);
}

TEST(count_novoices_comments_st, zero_bad_voices)
{
    int size = 100;
    Comment_static* comments = create_array(size);
    fill_array(comments, size);
    EXPECT_EQ(count_novoices_comments_st(comments, size), 0);
    free(comments);
}

TEST(count_novoices_comments_st, only_bad_voices)
{
    int size = 100;
    Comment_static* comments = create_array(size);
    fill_array_zeros(comments, size);
    EXPECT_EQ(count_novoices_comments_st(comments, size), size);
    free(comments);
}

TEST(count_novoices_comments_st, ten_million_voices)
{
    int size = 10000000;
    Comment_static* comments = create_array(size);
    if (!comments)
        return;
    int result = fill_array_dif_values(comments, size);
    EXPECT_EQ(count_novoices_comments_st(comments, size), result);
    free(comments);
}

TEST(read_array_from_file_st, not_existing_file)
{
    Comment_static* comments = NULL;
    int size = 0;
    const char* filename = "../../test_files/not_existing_file.txt";
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), FILE_OPEN_ERROR);
}

TEST(read_array_from_file_st, empty_file)
{
    const char* filename = "../../test_files/empty_file.txt";
    int size = 0;
    Comment_static* comments = NULL;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), EMPTY_FILE_ERROR);
}

TEST(read_array_from_file_st, number_of_comments_not_int)
{
    const char* filename = "../../test_files/fscanf_number_of_comments.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), FSCANF_NUMBER_OF_COMMENTS_ERROR);
    free(comments);
}

TEST(read_array_from_file_st, invalid_voices)
{
    const char* filename = "../../test_files/invalid_voices.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), INVALID_VOICES_ERROR);
}

TEST(read_array_from_file_st, invalid_mark)
{
    const char* filename = "../../test_files/invalid_mark.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), INVALID_MARK_ERROR);
}

TEST(read_array_from_file_st, big_file)
{
    const char* filename = "../../test_files/one_million_nodes.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), SUCCESS);
    free(comments);
}

TEST(read_array_from_file_st, cant_read_mark)
{
    const char* filename = "../../test_files/fscanf_mark.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), FSCANF_MARK_ERROR);
}

TEST(read_array_from_file_st, cant_read_voices)
{
    const char* filename = "../../test_files/fscanf_voices.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), FSCANF_VOICES_ERROR);
}

TEST(read_array_from_file_st, cant_read_id)
{
    const char* filename = "../../test_files/fscanf_id.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), FSCANF_ID_ERROR);
}

TEST(read_array_from_file_st, invalid_number_of_comments)
{
    const char* filename = "../../test_files/not_positive_number_of_comments.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), NOT_POSITIVE_NUMBER_OF_COMMENTS_ERROR);
}

// Number of comments is more than actual number of comments in file
TEST(read_array_from_file_st, incorrect_number_of_comments)
{
    const char* filename = "../../test_files/incorrect_number_of_comments.txt";
    Comment_static* comments = NULL;
    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments, &size), INCORRECT_NUMBER_OF_COMMENTS_ERROR);
}

TEST(read_array_from_file_st, correct_file)
{
    const char* filename = "../../test_files/correct_file.txt";
    Comment_static* comments_in_file = NULL;
    Comment_static comments[4] = {
            {0, 0, 0}, {1, 2.3, 5}, {2, 4.5, 521}, {3, 3.3, 10}
    };

    int size = 0;
    EXPECT_EQ(read_array_from_file_st(filename, &comments_in_file, &size), SUCCESS);
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

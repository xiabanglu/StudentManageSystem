#include <stdio.h>
#include <search.h>
#include <event.h>
#include <stdlib.h>
#include <log.h>
#include <math.h>


typedef struct {
    int fail;    // 不及格人数
    int pass;    // 及格人数
    int good;    // 良好人数
    int excellent; // 优秀人数
} ScoreLevelCount;

// 班级某学科最高分
double getClazzSubjectMax(Clazz *clazz, int subjectIdx);

// 年级某学科最高分
double getGradeSubjectMax(Grade *grade, int subjectIdx);

// 班级某学科平均分
double getClazzSubjectAvg(Clazz *clazz, int subjectIdx);

// 班级某学科方差
double getClazzSubjectVariance(Clazz *clazz, int subjectIdx);

// 班级某学科中位数
double getClazzSubjectMedian(Clazz *clazz, int subjectIdx);

// 年级某学科平均分
double getGradeSubjectAvg(Grade *grade, int subjectIdx);

// 年级某学科方差
double getGradeSubjectVariance(Grade *grade, int subjectIdx);

// 年级某学科中位数
double getGradeSubjectMedian(Grade *grade, int subjectIdx);

// 班级总分平均分
double getClazzTotalAvg(Clazz *clazz);

// 年级总分平均分
double getGradeTotalAvg(Grade *grade);

// 班级某学科分数等级人数统计
ScoreLevelCount countClazzSubjectLevels(Clazz *clazz, int subjectIdx);

// 年级某学科分数等级人数统计
ScoreLevelCount countGradeSubjectLevels(Grade *grade, int subjectIdx);



// clazz: 班级指针, subjectIdx: 学科下标(0-9)
double getClazzSubjectMax(Clazz *clazz, int subjectIdx) {
    double max = -1;
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu && stu->score[subjectIdx] > max)
            max = stu->score[subjectIdx];
    }
    return max;
}
double getGradeSubjectMax(Grade *grade, int subjectIdx) {
    double max = -1;
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        double clazzMax = getClazzSubjectMax(clazz, subjectIdx);
        if (clazzMax > max)
            max = clazzMax;
    }
    return max;
}
double getClazzSubjectAvg(Clazz *clazz, int subjectIdx) {
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu) {
            sum += stu->score[subjectIdx];
            cnt++;
        }
    }
    return cnt ? sum / cnt : 0;
}

double getClazzSubjectVariance(Clazz *clazz, int subjectIdx) {
    double mean = getClazzSubjectAvg(clazz, subjectIdx);
    double variance = 0;
    int cnt = 0;
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu) {
            variance += (stu->score[subjectIdx] - mean) * (stu->score[subjectIdx] - mean);
            cnt++;
        }
    }
    return cnt ? variance / cnt : 0;
}
#include <stdlib.h>
int cmpDouble(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    return (diff > 0) - (diff < 0);
}
double getClazzSubjectMedian(Clazz *clazz, int subjectIdx) {
    double temp[clazz->size];
    int cnt = 0;
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu) temp[cnt++] = stu->score[subjectIdx];
    }
    if (cnt == 0) return 0;
    qsort(temp, cnt, sizeof(double), cmpDouble);
    if (cnt % 2) return temp[cnt/2];
    else return (temp[cnt/2-1] + temp[cnt/2]) / 2.0;
}
double getGradeSubjectAvg(Grade *grade, int subjectIdx) {
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        for (int j = 0; j < clazz->size; j++) {
            Student *stu = clazz->students[j];
            if (stu) {
                sum += stu->score[subjectIdx];
                cnt++;
            }
        }
    }
    return cnt ? sum / cnt : 0;
}

double getGradeSubjectVariance(Grade *grade, int subjectIdx) {
    double mean = getGradeSubjectAvg(grade, subjectIdx);
    double variance = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        for (int j = 0; j < clazz->size; j++) {
            Student *stu = clazz->students[j];
            if (stu) {
                variance += (stu->score[subjectIdx] - mean) * (stu->score[subjectIdx] - mean);
                cnt++;
            }
        }
    }
    return cnt ? variance / cnt : 0;
}

double getGradeSubjectMedian(Grade *grade, int subjectIdx) {
    double temp[_MAX_STUDENT_NUM_PER_CLASS_ * _MAX_CLASS_NUM_PER_GRADE_];
    int cnt = 0;
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        for (int j = 0; j < clazz->size; j++) {
            Student *stu = clazz->students[j];
            if (stu) temp[cnt++] = stu->score[subjectIdx];
        }
    }
    if (cnt == 0) return 0;
    qsort(temp, cnt, sizeof(double), cmpDouble);
    if (cnt % 2) return temp[cnt/2];
    else return (temp[cnt/2-1] + temp[cnt/2]) / 2.0;
}
double getClazzTotalAvg(Clazz *clazz) {
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu) {
            sum += getSum(stu);
            cnt++;
        }
    }
    return cnt ? sum / cnt : 0;
}
double getGradeTotalAvg(Grade *grade) {
    double sum = 0;
    int cnt = 0;
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        for (int j = 0; j < clazz->size; j++) {
            Student *stu = clazz->students[j];
            if (stu) {
                sum += getSum(stu);
                cnt++;
            }
        }
    }
    return cnt ? sum / cnt : 0;
}
ScoreLevelCount countClazzSubjectLevels(Clazz *clazz, int subjectIdx) {
    ScoreLevelCount counter = {0, 0, 0, 0};
    for (int i = 0; i < clazz->size; i++) {
        Student *stu = clazz->students[i];
        if (stu) {
            double s = stu->score[subjectIdx];
            if (s < 60) counter.fail++;
            else if (s < 80) counter.pass++;
            else if (s < 90) counter.good++;
            else counter.excellent++;
        }
    }
    return counter;
}
//ScoreLevelCount c = countClazzSubjectLevels(clazz, 0);
//printf("语文 不及格:%d 及格:%d 良好:%d 优秀:%d\n", c.fail, c.pass, c.good, c.excellent);
//如需统计所有学科，可以循环 subjectIdx 0~9，分别调用上述函数即可。
ScoreLevelCount countGradeSubjectLevels(Grade *grade, int subjectIdx) {
    ScoreLevelCount counter = {0, 0, 0, 0};
    for (int i = 0; i < grade->size; i++) {
        Clazz *clazz = grade->classes[i];
        ScoreLevelCount c = countClazzSubjectLevels(clazz, subjectIdx);
        counter.fail      += c.fail;
        counter.pass      += c.pass;
        counter.good      += c.good;
        counter.excellent += c.excellent;
    }
    return counter;
}
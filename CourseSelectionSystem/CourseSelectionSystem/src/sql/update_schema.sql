-- 更新 courses 表结构
-- 假设原有表包含 id, name, capacity

-- 添加学分字段
ALTER TABLE courses ADD COLUMN IF NOT EXISTS credit REAL DEFAULT 0;

-- 添加教师ID字段
ALTER TABLE courses ADD COLUMN IF NOT EXISTS teacher_id VARCHAR(50);

-- 添加教师姓名子段 (在 teacher_id 之后，如果是新创建表)
ALTER TABLE courses ADD COLUMN IF NOT EXISTS teacher_name VARCHAR(100);

-- 添加上课时间字段 (星期几)
ALTER TABLE courses ADD COLUMN IF NOT EXISTS weekday INTEGER;

-- 添加上课时间字段 (节次)
ALTER TABLE courses ADD COLUMN IF NOT EXISTS timeslot INTEGER;

-- 为了支持时间冲突检测，建议添加索引
CREATE INDEX IF NOT EXISTS idx_courses_teacher_time ON courses(teacher_id, weekday, timeslot);

-- 如果 courses 表还不存在，则创建完整表 (参考)
CREATE TABLE IF NOT EXISTS courses (
    id VARCHAR(50) PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    capacity INTEGER DEFAULT 60,
    credit REAL DEFAULT 0,
    teacher_id VARCHAR(50),
    teacher_name VARCHAR(100),
    weekday INTEGER,
    timeslot INTEGER
);

-- 选课关联表 (供参考，Proxy 中已使用)
CREATE TABLE IF NOT EXISTS student_courses (
    student_id VARCHAR(50),
    course_id VARCHAR(50),
    PRIMARY KEY (student_id, course_id)
);

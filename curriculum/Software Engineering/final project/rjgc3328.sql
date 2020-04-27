create table record
(
    ACID   varchar(32)  not null,
    Worker varchar(32)  not null,
    Date   date         not null,
    detail varchar(128) null,
    constraint Record_users_Username_fk
        foreign key (Worker) references users (Username)
            on update cascade
);

INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'lee', '2019-12-02', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'jack', '2019-12-02', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'lee', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0003', 'lee', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0002', 'lee', '2019-12-03', 'normalest');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'jack', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0003', 'jack', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0002', 'jack', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'lee', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0002', 'john', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'alice', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'alice', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'lee', '2019-12-03', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'lee', '2019-12-04', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0003', 'lee', '2019-12-04', 'damage');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'lee', '2019-12-04', 'cannot work');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'lee', '2019-12-04', 'noisy');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'jack', '2019-12-04', 'broken');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'john', '2019-12-04', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'john', '2019-12-04', 'broken');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0006', 'lee', '2019-12-05', 'wires damage');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'lee', '2019-12-05', 'Damaged housing');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'lee', '2019-12-05', 'Compressor failure');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'jack', '2019-12-05', 'normally');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0003', 'john', '2019-12-05', 'Compressor failure');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'john', '2019-12-05', 'Compressor failure');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'alice', '2019-12-05', 'wires damaged');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'john', '2019-12-05', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'john', '2019-12-05', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'frank', '2019-12-05', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0001', 'lee', '2019-12-06', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0005', 'lee', '2019-12-06', 'compressor damaged');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0007', 'lee', '2019-12-06', 'functional error');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0002', 'jack', '2019-12-06', 'fixed');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0006', 'jack', '2019-12-06', 'checking');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0003', 'john', '2019-12-06', 'normal');
INSERT INTO rjgc3328.record (ACID, Worker, Date, detail) VALUES ('0004', 'alice', '2019-12-06', 'normal');
create table users
(
    Username varchar(32) not null,
    Password varchar(32) not null,
    constraint Users_Username_uindex
        unique (Username)
);

alter table users
    add primary key (Username);

INSERT INTO rjgc3328.users (Username, Password) VALUES ('Administrator', 'rjgc123');
INSERT INTO rjgc3328.users (Username, Password) VALUES ('alice', 'alice');
INSERT INTO rjgc3328.users (Username, Password) VALUES ('frank', 'frank');
INSERT INTO rjgc3328.users (Username, Password) VALUES ('jack', 'jack');
INSERT INTO rjgc3328.users (Username, Password) VALUES ('john', 'john');
INSERT INTO rjgc3328.users (Username, Password) VALUES ('lee', 'lee');
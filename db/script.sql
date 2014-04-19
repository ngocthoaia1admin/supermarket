SET @OLD_UNIQUE_CHECKS=@@UNIQUE_CHECKS, UNIQUE_CHECKS=0;
SET @OLD_FOREIGN_KEY_CHECKS=@@FOREIGN_KEY_CHECKS, FOREIGN_KEY_CHECKS=0;
SET @OLD_SQL_MODE=@@SQL_MODE, SQL_MODE='TRADITIONAL';

DROP SCHEMA IF EXISTS `supermarket` ;
CREATE SCHEMA IF NOT EXISTS `supermarket` DEFAULT CHARACTER SET utf8 COLLATE utf8_unicode_ci ;
USE `supermarket` ;

-- -----------------------------------------------------
-- Table `supermarket`.`roles`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`roles` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`roles` (
  `id` INT NOT NULL ,
  `name` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `supermarket`.`users`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`users` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`users` (
  `id` INT NOT NULL ,
  `name` VARCHAR(45) NULL ,
  `sdt` VARCHAR(45) NULL ,
  `dia_chi` VARCHAR(50) NULL ,
  `role_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_users_roles1` (`role_id` ASC) ,
  CONSTRAINT `fk_users_roles1`
    FOREIGN KEY (`role_id` )
    REFERENCES `supermarket`.`roles` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `supermarket`.`orders`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`orders` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`orders` (
  `id` INT NOT NULL ,
  `date` DATE NULL ,
  `user_id` INT NOT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_orders_users1` (`user_id` ASC) ,
  CONSTRAINT `fk_orders_users1`
    FOREIGN KEY (`user_id` )
    REFERENCES `supermarket`.`users` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `supermarket`.`lines`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`lines` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`lines` (
  `id` INT NOT NULL ,
  `name` VARCHAR(45) NULL ,
  `description` VARCHAR(45) NULL ,
  PRIMARY KEY (`id`) )
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `supermarket`.`products`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`products` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`products` (
  `id` INT NOT NULL ,
  `name` VARCHAR(45) NULL ,
  `quantity` INT NULL ,
  `line_id` INT NOT NULL ,
  `price` DOUBLE NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_products_lines1` (`line_id` ASC) ,
  CONSTRAINT `fk_products_lines1`
    FOREIGN KEY (`line_id` )
    REFERENCES `supermarket`.`lines` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;


-- -----------------------------------------------------
-- Table `supermarket`.`order_details`
-- -----------------------------------------------------
DROP TABLE IF EXISTS `supermarket`.`order_details` ;

CREATE  TABLE IF NOT EXISTS `supermarket`.`order_details` (
  `id` INT NOT NULL ,
  `order_id` INT NOT NULL ,
  `product_id` INT NOT NULL ,
  `quantity` INT NULL ,
  PRIMARY KEY (`id`) ,
  INDEX `fk_order_details_orders1` (`order_id` ASC) ,
  INDEX `fk_order_details_products1` (`product_id` ASC) ,
  CONSTRAINT `fk_order_details_orders1`
    FOREIGN KEY (`order_id` )
    REFERENCES `supermarket`.`orders` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION,
  CONSTRAINT `fk_order_details_products1`
    FOREIGN KEY (`product_id` )
    REFERENCES `supermarket`.`products` (`id` )
    ON DELETE NO ACTION
    ON UPDATE NO ACTION)
ENGINE = InnoDB;



SET SQL_MODE=@OLD_SQL_MODE;
SET FOREIGN_KEY_CHECKS=@OLD_FOREIGN_KEY_CHECKS;
SET UNIQUE_CHECKS=@OLD_UNIQUE_CHECKS;

-- -----------------------------------------------------
-- Data for table `supermarket`.`roles`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`roles` (`id`, `name`) VALUES (1, 'admin');
INSERT INTO `supermarket`.`roles` (`id`, `name`) VALUES (2, 'employee');

COMMIT;

-- -----------------------------------------------------
-- Data for table `supermarket`.`users`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`users` (`id`, `name`, `sdt`, `dia_chi`, `role_id`) VALUES (1, 'admin', '1234646', 'slfjaslfasjfl', 1);
INSERT INTO `supermarket`.`users` (`id`, `name`, `sdt`, `dia_chi`, `role_id`) VALUES (2, 'employee', '2302380', 'lsdfjalsfjl', 2);

COMMIT;

-- -----------------------------------------------------
-- Data for table `supermarket`.`orders`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`orders` (`id`, `date`, `user_id`) VALUES (1, '2000/6/2', 2);
INSERT INTO `supermarket`.`orders` (`id`, `date`, `user_id`) VALUES (2, '2001/6/7', 2);

COMMIT;

-- -----------------------------------------------------
-- Data for table `supermarket`.`lines`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`lines` (`id`, `name`, `description`) VALUES (1, 'may tinh', NULL);
INSERT INTO `supermarket`.`lines` (`id`, `name`, `description`) VALUES (2, 'dien thoai', NULL);
INSERT INTO `supermarket`.`lines` (`id`, `name`, `description`) VALUES (3, 'gia dung', NULL);

COMMIT;

-- -----------------------------------------------------
-- Data for table `supermarket`.`products`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (1, 'may tinh tosiba1', 100, 1, 10000000);
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (2, 'May tinh dell 1', 500, 1, 14000000);
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (3, 'May tinh lenovo 1', 600, 1, 17900000);
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (4, 'Điện thoại Nokia', 300, 2, 4000000);
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (5, 'Điện thoại Samsung', 500, 2, 5000000);
INSERT INTO `supermarket`.`products` (`id`, `name`, `quantity`, `line_id`, `price`) VALUES (6, 'Tu lanh', 200, 3, 8000000);

COMMIT;

-- -----------------------------------------------------
-- Data for table `supermarket`.`order_details`
-- -----------------------------------------------------
START TRANSACTION;
USE `supermarket`;
INSERT INTO `supermarket`.`order_details` (`id`, `order_id`, `product_id`, `quantity`) VALUES (1, 1, 1, 5);
INSERT INTO `supermarket`.`order_details` (`id`, `order_id`, `product_id`, `quantity`) VALUES (2, 1, 2, 3);
INSERT INTO `supermarket`.`order_details` (`id`, `order_id`, `product_id`, `quantity`) VALUES (3, 2, 2, 5);
INSERT INTO `supermarket`.`order_details` (`id`, `order_id`, `product_id`, `quantity`) VALUES (4, 2, 3, 1);
INSERT INTO `supermarket`.`order_details` (`id`, `order_id`, `product_id`, `quantity`) VALUES (5, 2, 2, 1);

COMMIT;
